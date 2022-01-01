#pragma once

#include "Net/ISocketFactory.h"

class RealSocketFactory : public ISocketFactory
{
public:
    RealSocketFactory();
    ~RealSocketFactory();

    virtual ISocket * create() override;

    virtual void destroy(ISocket * s) override;

    virtual void remove(ISocket * s) override;

    virtual ISocket * wait(const std::string & address) override;

private:
    std::vector<ISocket*> m_vectOfSock;

};

