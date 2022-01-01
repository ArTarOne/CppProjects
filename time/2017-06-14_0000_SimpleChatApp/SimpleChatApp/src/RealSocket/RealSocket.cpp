#include "OopSocket/OopSocket.h"
#include "StdPlus/StdPlus.h"


#include "RealSocket.h"

#include "SupportFunctions.hpp"



RealSocket::~RealSocket()
{

}


void RealSocket::connect(const std::string & address)
{
    std::string ip;
    uint16_t    port;

    splitIpAndPort(address, ip, port);
    SocketAddress serverAdress(ip,port);
    m_socket->Connect(serverAdress);
    AMSG("Connect ok");

    m_isConnected = true;
}


long long RealSocket::send(const char * buf, long long bufSize)
{
    if (!m_isConnected)
        throw std::logic_error("ERROR: you try send before connect in RealSocket::send");

    return m_socket->Send(buf, static_cast<size_t>(bufSize));
}

long long RealSocket::recv(char * buf, long long bufSize)
{
    if (!m_isConnected)
        throw std::logic_error("ERROR: you try recv before connect in RealSocket::recv");

    return m_socket->ReceiveFullSize(buf, static_cast<size_t>(bufSize));
}



