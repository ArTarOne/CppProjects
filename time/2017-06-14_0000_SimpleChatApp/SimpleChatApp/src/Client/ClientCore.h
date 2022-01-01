#pragma once

class User;
class NetworkMap;

class ClientCore
{
public:
    ClientCore();
    ~ClientCore();

    void connect(const std::string & addressForConnect);
    void disconnect();
    NetworkMap getNetworkMap();
    std::vector<UserData> getClients();
    MsgContainer getMessages();
    void sendData(const int id_to, const std::string & data);
    bool isConnecting();

private:
    void recvData();
    void sendMsgs();
  

    std::string         m_address;
    RealSocketFactory * m_realSocketFactory = nullptr;
    ISocket *           m_socket            = nullptr;
    MsgContainer        m_outMessages;
    MsgContainer        m_inputMessages;


    int m_ping = 0;

    NetworkMap           m_networkMap;
    bool                 m_isClientWork      = true;

  
   
    std::thread          m_recievingThread;


    std::mutex m_netMapMsgsMutex;
    std::mutex m_socketMutex;


};

