#include "OopSocket/OopSocket.h"
#include "StdPlus/StdPlus.h"


#include "RealSocketFactory.h"
#include "RealSocket.h"

#include "SupportFunctions.hpp"


RealSocketFactory::RealSocketFactory()
{

}

RealSocketFactory::~RealSocketFactory()
{
    for (unsigned i = 0; i < m_vectOfSock.size(); i++)
        destroy(m_vectOfSock[i]);
}

ISocket * RealSocketFactory::create()
{
    RealSocket * sock = new RealSocket;

    SocketUtil sockInit{};

    if (!sockInit.StaticInit())
        throw std::logic_error("ERROR: !sockInit.StaticInit() in RealSocketFactory::create");

    sock->m_socket = sockInit.CreateTCPSocket(INET);

    m_vectOfSock.push_back(sock);

    return sock;
}

ISocket * RealSocketFactory::wait(const std::string & address)
{
    //  AFUN;

    ISocket * IlistenSock = create();
    RealSocket * RealListenSocket = dynamic_cast<RealSocket*>(IlistenSock);


    std::string ip;
    uint16_t    port;
    splitIpAndPort(address, ip, port);
    SocketAddress serverAdress(ip, port);

    RealListenSocket->m_socket->Bind(serverAdress);
    AMSG("bind ok");
    RealListenSocket->m_socket->Listen();
    AMSG("listen ok");

    RealSocket * clentSock = new RealSocket;
    SocketAddress clientAdress;
    AMSG("accepting...");
    clentSock->m_socket = RealListenSocket->m_socket->Accept(clientAdress);
    clentSock->m_isConnected = true;
    AMSG("accept ok");

    destroy(IlistenSock);

    m_vectOfSock.push_back(clentSock);

    return clentSock;

}

void RealSocketFactory::destroy(ISocket * s)
{
    auto itCurSocket = std::find(m_vectOfSock.begin(), m_vectOfSock.end(), s);

    if (itCurSocket == m_vectOfSock.end())
        throw std::logic_error("ERROR: cannot destroy socket in RealSocketFactory::destroy");

    remove(s);
    delete s;

}

void RealSocketFactory::remove(ISocket * s)
{
    m_vectOfSock.erase(std::remove(m_vectOfSock.begin(), m_vectOfSock.end(), s)
        , m_vectOfSock.end());
}



