#pragma once

//#include <network/IServerSession.h>
#include "../include/network/IServerSession.h"

class EchoSession : public IServerSession, public std::enable_shared_from_this<EchoSession>
{
public:
    EchoSession() = default;

    virtual std::future<void> Run(tcp::socket sock) override;
};

class EchoSessionCreator : public IServerSessionCreator
{
public:
    EchoSessionCreator() = default;
    virtual ~EchoSessionCreator() = default;

    IServerSessionPtr CreateSession() override
    {
        return boost::shared_ptr<IServerSession>(new EchoSession());
    }
};