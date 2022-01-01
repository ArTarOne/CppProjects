#pragma once

#include "ISocket.h"


// Pattern Factory for ISocket
class ISocketFactory
{
    virtual ISocket * create() = 0;

    // wait connect
    // listen socket must be destroy inside
    virtual ISocket * wait(const std::string & address) = 0;

    // call destructor
    virtual void destroy(ISocket * s) = 0;

    // NOT call destructor. Only delete from list
    virtual void remove(ISocket * s) = 0;
};

