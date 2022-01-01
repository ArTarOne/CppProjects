#include "OopSocket/OopSocket.h"
#include "StdPlus/StdPlus.h"

#include "RealSocket/RealSocketFactory.h"
#include "RealSocket/RealSocket.h"

#include "Net/ISocketStream.hpp"
#include "RealSocket/SupportFunctions.hpp"

#include "ClientCore.h"
#include "NetworkMap.h"

#include "User/User.h"

ClientCore::ClientCore()
{
    m_realSocketFactory = new RealSocketFactory();
    m_socket = m_realSocketFactory->create();
}

ClientCore::~ClientCore()
{
    disconnect();
    delete m_realSocketFactory;
}

void ClientCore::connect(const std::string & addressForConnect)
{
    m_address = addressForConnect;
    m_socket->connect(m_address);
    m_isClientWork = true;
    RealSocket * RealSock = dynamic_cast<RealSocket*>(m_socket);

    int id;
    *m_socket >> id;
    AVAR(id);

    RealSock->socket()->SetNonBlockingMode(true);

    m_recievingThread = std::thread{ &ClientCore::recvData, this };

}

void ClientCore::disconnect()
{
    m_isClientWork = false;
    m_recievingThread.join();
    m_realSocketFactory->destroy(m_socket);
}



NetworkMap ClientCore::getNetworkMap()
{
    std::lock_guard<std::mutex>l(m_netMapMsgsMutex);
    NetworkMap inp = m_networkMap;
    m_networkMap.m_clientList.clear();
    m_networkMap.m_msgs.clear();
    return inp;
}

std::vector<UserData> ClientCore::getClients()
{
    std::lock_guard<std::mutex>l(m_netMapMsgsMutex);
    std::vector<UserData> inp = m_networkMap.m_clientList;
    m_networkMap.m_clientList.clear();
    return inp;
}


MsgContainer ClientCore::getMessages()
{
    std::lock_guard<std::mutex>l(m_netMapMsgsMutex);
    MsgContainer inp = m_networkMap.m_msgs;
    m_networkMap.m_msgs.clear();
    return inp;
}




void ClientCore::sendData(const int id_to, const std::string & data)
{
    MsgData sendingMsg;
    sendingMsg.m_to = id_to;
    sendingMsg.m_msg = data;
    m_outMessages.push_back(sendingMsg);
    sendMsgs();
}


bool ClientCore::isConnecting()
{
    return m_isClientWork;
}

void ClientCore::recvData()
{
    const int MAX_PING = 1000;
    while (m_ping < MAX_PING)
    {
        const int THREAD_PAUSE_MS = 100;
        stdplus::thread_sleep(THREAD_PAUSE_MS);

        NetworkMap nM;

        try
        {
            std::lock_guard<std::mutex>l(m_socketMutex);
            *m_socket >> nM;
            m_ping = 0;
        }
        catch (const std::logic_error &)
        {
            m_ping++;
            continue;
        }

        {
            std::lock_guard<std::mutex>l(m_netMapMsgsMutex);

            m_networkMap.m_clientList.clear();
            m_networkMap.m_clientList.insert(m_networkMap.m_clientList.end(),
                nM.m_clientList.begin(), nM.m_clientList.end());

            m_networkMap.m_msgs.insert(m_networkMap.m_msgs.end(),
                nM.m_msgs.begin(), nM.m_msgs.end());
        }
    }

    AMSG("Server Shundown");
    disconnect();
}

void ClientCore::sendMsgs()
{
    if (m_isClientWork == true)
    {
        std::lock_guard<std::mutex>l(m_socketMutex);
        *m_socket << m_outMessages;
        m_outMessages.clear();
    }
    else
        AMSG("Clent was disconected");
}



