#pragma once

#include "Net/ISocket.h"



class ISocketFactory;
class RealSocketFactory;
class TCPSocket;

typedef std::shared_ptr< TCPSocket > TCPSocketPtr;

class RealSocket : public ISocket
{
    friend  RealSocketFactory;

public:

    ~RealSocket();

    virtual void connect(const std::string & address) override;

    virtual long long send(const char * buf, long long bufSize) override;

    virtual long long recv(char * buf, long long bufSize) override;

    TCPSocketPtr socket() const { return m_socket; }

private:

    TCPSocketPtr m_socket;
    bool         m_isConnected = false;

};
