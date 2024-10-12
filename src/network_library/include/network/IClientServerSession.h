#pragma once

//#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/shared_array.hpp>

#include "net_asio.h"

class IClientServerSession
{
public:
    virtual ~IClientServerSession() = default;
    virtual std::future<void> Run(tcp::socket serverSock, const std::vector<boost::shared_ptr<tcp::socket>>& clientsSockets) = 0;
};

using IClientServerSessionPtr = boost::shared_ptr<IClientServerSession>;

//TODO move to separated file
class IClientServerSessionCreator
{
public:
    virtual ~IClientServerSessionCreator() = default;

    virtual boost::shared_ptr<IClientServerSession> CreateSession() = 0;
};

using IClientServerSessionCreatorPtr = boost::shared_ptr<IClientServerSessionCreator>;