#pragma once

class User;
class NetworkMap;

class Server
{
    friend void listenThread(Server &);

public:
    Server();
    ~Server();

    void start(std::string address);

private:

    void mainLoop();
   
    std::string         m_address;
    RealSocketFactory * m_socketFactory = nullptr;
    std::mutex          m_usersMutex;
    std::thread         m_newConnectsThread;
    std::vector<User>   m_users;
    bool                m_isListenWork  = true;
};


void listenThread(Server & s);
