#pragma once

#include <string>

class ISocketFactory;

class ISocket
{
    friend class ISocketFactory;

public:

    // for example: 123.234.123.123:1235
    // if wrong, throw exeption logic_error
    virtual void connect(const std::string & address) = 0;

    // if wrong, throw exeption logic_error
    // return count sent bytes
    virtual long long send(const char * buf, long long bufSize) = 0;

    // if wrong, throw exeption logic_error
    // return count recv bytes
    virtual long long recv(char * buf, long long bufSize) = 0;

    virtual ~ISocket() {}

private:


};

