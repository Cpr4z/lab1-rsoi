#pragma once

//#include <network/IClientServerSession.h>
#include "../include/network/IClientServerSession.h"
#include "../include/request_handler/IClientServerRequestHandler.h"

class HttpClientServerSession : public IClientServerSession
{
public:
    HttpClientServerSession(const IClientServerReqHandlerCreatorPtr &creator);

    virtual std::future<void> Run(tcp::socket server_sock,
                                  const std::vector<boost::shared_ptr<tcp::socket>> &clients_sock) override;

private:
    IClientServerReqHandlerCreatorPtr m_handlerCreator;
};

class HttpClientServerSessionCreator : public IClientServerSessionCreator
{
public:
    HttpClientServerSessionCreator(const IClientServerReqHandlerCreatorPtr &creator);
    virtual ~HttpClientServerSessionCreator() = default;

    IClientServerSessionPtr CreateSession() override
    {
        return boost::shared_ptr<IClientServerSession>(new HttpClientServerSession(m_creator));
    }

private:
    IClientServerReqHandlerCreatorPtr m_creator;
};