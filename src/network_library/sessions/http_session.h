#pragma once

#include "../include/network/IServerSession.h"
#include "../include/request_handler/IServerRequestHandler.h"

class HttpServerSession : public IServerSession
{
public:
    HttpServerSession(const IServerReqHandlerCreatorPtr &creator);
    ~HttpServerSession();

    virtual std::future<void> Run(tcp::socket sock) override;

private:
    http::request<http::string_body> m_req;
    IServerReqHandlerCreatorPtr m_handlerCreator;
};

class HttpServerSessionCreator : public IServerSessionCreator
{
public:
    HttpServerSessionCreator(const IServerReqHandlerCreatorPtr &creator);
    virtual ~HttpServerSessionCreator() = default;

    IServerSessionPtr CreateSession() override
    {
        return boost::shared_ptr<IServerSession>(new HttpServerSession(m_handlerCreator));
    }

private:
    IServerReqHandlerCreatorPtr m_handlerCreator;
};