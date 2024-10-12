#pragma once

#include <config/IConfig.h>

#include "../../base/include/config/base_constants.h"

#include <functional>
#include <map>
#include <memory>

#include "../request_response_support/RequestResponse.h"

// TODO разбить по файлам
class IClientServerReqHandler
{
public:
    enum state_t
    {
        RES_CONTINUE,
        RES_REPEAT,
        RES_END
    };

    virtual ~IClientServerReqHandler() = default;
    virtual state_t HandleRequest(const IRequestPtr &req) = 0;
    virtual state_t GetNextRequest(const IRequestPtr &req, size_t &client_index) = 0;
    virtual state_t HandleResponse(const IResponsePtr &resp) = 0;
    virtual void MakeResponse(const IResponsePtr &resp) = 0;

protected:
    std::map<std::string, size_t> m_clientIndexes;
    void SetClientIndexes(const IConfigPtr &config)
    {
        m_clientIndexes.clear();
        std::vector<std::string> clients = config->GetStringArray({AppLiterals::Clients});

        for (size_t i = 0; i < clients.size(); i++)
            m_clientIndexes[clients[i]] = i;
    }
};

using IClientServerReqHandlerPtr = boost::shared_ptr<IClientServerReqHandler>;

class IClientServerReqHandlerCreator
{
public:
    virtual ~IClientServerReqHandlerCreator() = default;

    virtual IClientServerReqHandlerPtr CreateHandler() const = 0;
};

using IClientServerReqHandlerCreatorPtr = boost::shared_ptr<IClientServerReqHandlerCreator>;

template <class T>
concept base_client_server_handler = std::is_base_of<IClientServerReqHandler, T>::value;

template <base_client_server_handler T>
class ClientServerReqHandlerCreator : public IClientServerReqHandlerCreator
{
public:
    template <typename... Args> ClientServerReqHandlerCreator(Args... args)
    {
        create_func_ = [args...]() { return boost::shared_ptr<IClientServerReqHandler>(new T(args...)); };
    }

    ~ClientServerReqHandlerCreator() = default;

    IClientServerReqHandlerPtr CreateHandler() const override
    {
        return create_func_();
    }

private:
    std::function<IClientServerReqHandlerPtr()> create_func_;
};