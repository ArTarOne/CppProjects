#include "OopSocket/OopSocket.h"
#include "StdPlus/StdPlus.h"

#include "RealSocket/RealSocketFactory.h"
#include "RealSocket/RealSocket.h"

#include "Net/ISocketStream.hpp"

#include "RealSocket/SupportFunctions.hpp"

#include "Server.h"

#include "User/User.h"


#include "Client/NetworkMap.h"


Server::Server()
{
    m_socketFactory = new RealSocketFactory();
}

Server::~Server()
{
    m_isListenWork = false;
    m_newConnectsThread.join();
    delete m_socketFactory;
}

void Server::start(std::string address)
{
    m_address = address;
    m_newConnectsThread = std::thread{ listenThread, std::ref(*this) };
    while (true)
    {
        try
        {
            mainLoop();
        }
        catch (std::logic_error & exceptionInServerStart)
        {
            AVAR(exceptionInServerStart.what());
        }
        const int THREAD_PAUSE_MS = 200;
        stdplus::thread_sleep(THREAD_PAUSE_MS);

    //    AVAR(m_users);
    }
}

void Server::mainLoop()
{
    ASPLIT;

    MsgContainer broadcastMessages;
    std::lock_guard<std::mutex>l(m_usersMutex);

    std::vector<User> disconectedClients;

    for (auto & waitingUser : m_users)
    {
        ISocket & curSocket = *waitingUser.m_ptrUserSocket;

        try
        {
            MsgContainer newMessages;
            curSocket >> newMessages;

            waitingUser.m_storeMessages.insert(waitingUser.m_storeMessages.end(),
                newMessages.begin(), newMessages.end());

            for (auto & msg : waitingUser.m_storeMessages)
            {
                msg.m_from = waitingUser.m_userData.m_id;
                AVAR(msg);
            }
        }
        catch (const std::logic_error &)
        {
            continue;
        }

        NetworkMap sendingClientData;
        auto & sendingClientList = sendingClientData.m_clientList;

        for (auto & sendingUser : m_users)
        {
            AMSG("IN SENDING USER");
            sendingClientList.push_back(sendingUser.m_userData);

            auto & storeMessages = sendingUser.m_storeMessages;
            AVAR(storeMessages.size());
            auto it = storeMessages.begin();
            auto itEnd = storeMessages.end();

            std::vector<std::list<MsgData>::iterator> itForDeleteAfterSending;

            for (; it != itEnd; ++it)
            {
                auto & sendingMsg = *it;

                if (sendingMsg.m_to == waitingUser.m_userData.m_id)
                {
                    AMSG("ADD CONCRETE USER MSG");
                    itForDeleteAfterSending.push_back(it);
                    sendingClientData.m_msgs.push_back(sendingMsg);
                }
                else if (sendingMsg.m_to == 0)
                {
                    AMSG("ADD BROADCAST USER MSG");
                    itForDeleteAfterSending.push_back(it);
                    broadcastMessages.push_back(sendingMsg);
                }
                else
                {
                    AMSG("Not user with id=" + stdplus::to_string(sendingMsg.m_to));
                }
            }

            for (auto & itDel : itForDeleteAfterSending)
            {
                storeMessages.erase(itDel);
            }

            AVAR(sendingClientData.m_msgs.size());

        }
        try
        {
            curSocket << sendingClientData;
        }
        catch (std::logic_error & exceptionInSendMainLoop)
        {
            AVAR(exceptionInSendMainLoop.what());
            m_socketFactory->destroy(waitingUser.m_ptrUserSocket);
            disconectedClients.push_back(waitingUser);
        }
    }

    NetworkMap broadcastSendingData;

    for (auto & waitingUser : m_users)
    {
        broadcastSendingData.m_clientList.push_back(waitingUser.m_userData);
    }

    broadcastSendingData.m_msgs = broadcastMessages;

    for (auto & waitingUser : m_users)
    {
        try
        {
            *waitingUser.m_ptrUserSocket << broadcastSendingData;
        }
        catch (std::logic_error & exceptionInSendMainLoop)
        {
            AVAR(exceptionInSendMainLoop.what());
            m_socketFactory->destroy(waitingUser.m_ptrUserSocket);
            disconectedClients.push_back(waitingUser);
        }
    }
    if (!disconectedClients.empty())
    {
        for (auto & deletingUser : disconectedClients)
        {
            m_users.erase(remove(m_users.begin(), m_users.end(), deletingUser), m_users.end());
        }
        disconectedClients.clear();
    }
}

void listenThread(Server & s)
{
    AMSG("Start listen thread");

    while (s.m_isListenWork)
    {
        ISocket * newClientSocket = s.m_socketFactory->wait(s.m_address);
        {
            std::lock_guard<std::mutex>l(s.m_usersMutex);
            User newUser = makeNewUser(newClientSocket);
            s.m_users.push_back(newUser);
            *newUser.m_ptrUserSocket << newUser.m_userData.m_id;
        }
        RealSocket * RealSock = dynamic_cast<RealSocket*>(newClientSocket);
        RealSock->socket()->SetNonBlockingMode(true);
    }

    AMSG("Finish listen thread");
}

