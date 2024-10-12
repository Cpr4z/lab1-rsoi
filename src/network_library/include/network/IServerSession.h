#pragma once

#include "net_asio.h"

#include <boost/shared_ptr.hpp>

class IServerSession
{
public:
    virtual ~IServerSession() = default;
    virtual std::future<void> Run(tcp::socket socket) = 0; // TODO refactor arg socket
};

using IServerSessionPtr = boost::shared_ptr<IServerSession>;

class IServerSessionCreator
{
public:
    virtual ~IServerSessionCreator() = default;

    virtual IServerSessionPtr CreateSession() = 0;
};

using IServerSessionCreatorPtr  = boost::shared_ptr<IServerSessionCreator>;