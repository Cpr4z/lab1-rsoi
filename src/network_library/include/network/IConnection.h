#pragma once

#include <boost/shared_ptr.hpp>

class IConnection
{
public:
    virtual void Run() = 0;

    virtual ~IConnection() = default;
};

using IConnectionPtr = boost::shared_ptr<IConnection>;