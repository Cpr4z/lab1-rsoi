#pragma once

#include <functional>
//#include <memory>
#include <boost/smart_ptr/make_shared.hpp>

#include "../request_response_support/RequestResponse.h"

// TODO разбить по файлам
class IServerReqHandler
{
public:
    virtual ~IServerReqHandler() = default;

    virtual void HandleRequest(const IRequestPtr &req) = 0;
    virtual void MakeResponse(const IResponsePtr &resp) = 0;
};

using IServerReqHandlerPtr = boost::shared_ptr<IServerReqHandler>;

class IServerReqHandlerCreator
{
public:
    virtual ~IServerReqHandlerCreator() = default;

    virtual IServerReqHandlerPtr CreateHandler() const = 0;
};

using IServerReqHandlerCreatorPtr = boost::shared_ptr<IServerReqHandlerCreator>;

template <class T>
concept base_server_handler = std::is_base_of<IServerReqHandler, T>::value;

template <base_server_handler T> class ServerReqHandlerCreator : public IServerReqHandlerCreator
{
public:
    template <typename... Args> ServerReqHandlerCreator(Args... args)
    {
        m_createFunc = [args...]() { return boost::make_shared<T>(args...); };
    }

    virtual ~ServerReqHandlerCreator() = default;

    IServerReqHandlerPtr CreateHandler() const override
    {
        return m_createFunc();
    }

private:
    std::function<IServerReqHandlerPtr()> m_createFunc;
};