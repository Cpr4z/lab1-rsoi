#include "PersonsServerHandler.h"

#include "../../network_library/include/router/router.h"
//#include <router/router.h>

#include "../../base/include/logger/LoggerFactory.h"
//#include <logger/LoggerFactory.h>

PersonsServerHandler::PersonsServerHandler(const IResponseFactoryPtr &respFactory) : m_respFactory(respFactory)
{
}

void PersonsServerHandler::HandleRequest(const IRequestPtr &req)
{
    LoggerFactory::createLogger()->logInfo((std::string("[persons]: get request: ") + req->GetTarget()).c_str());
    if (!req->GetBody().empty())
        LoggerFactory::createLogger()->logInfo((std::string("[persons]: request body: ") + req->GetBody()).c_str());

    static_req_handler_t route = RequestsRouter::Instanse()->RouteReq(req->GetTarget(), req->GetMethod());

    m_resp = m_respFactory->CreateResponse();
    if (route)
    {
        try
        {
            route(m_resp, req);
        }
        catch(const std::exception& e)
        {
            LoggerFactory::createLogger()->logError((std::string("[persons]: unhandled exception: ") + e.what()).c_str());
            m_resp->SetStatus(network::CODE_503);
            m_resp->SetBody("Server error");
        }

    }
    else
    {
        m_resp->SetStatus(network::CODE_404);
        m_resp->SetBody("Not found");
    }
}

void PersonsServerHandler::MakeResponse(const IResponsePtr &resp)
{
    resp->Copy(m_resp);
    LoggerFactory::createLogger()->logInfo((std::string("[persons]: sending response status: ") + std::to_string((int) resp->GetStatus())).c_str());
    if (!resp->GetBody().empty())
        LoggerFactory::createLogger()->logInfo((std::string("[persons]: sending response body: ") + resp->GetBody()).c_str());
}