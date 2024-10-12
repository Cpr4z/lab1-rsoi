#pragma once

#include "../../network_library/include/request_response_support/IResponseFactory.h"
#include "../../network_library/include/request_handler/IServerRequestHandler.h"
#include "../../base/include/config/IConfig.h"

class PersonsServerHandler : public IServerReqHandler
{
public:
    PersonsServerHandler(const IResponseFactoryPtr &respFactory);

    virtual void HandleRequest(const IRequestPtr &req) override;
    virtual void MakeResponse(const IResponsePtr &resp) override;

private:
    IResponseFactoryPtr m_respFactory;

    IResponsePtr m_resp;
};