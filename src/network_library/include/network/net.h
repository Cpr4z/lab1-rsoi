#pragma once

#include "net_asio.h"
#include "../../../base/include/config/IConfig.h"

#include "../request_response_support/IResponseFactory.h"
#include "../request_handler/IServerRequestHandler.h"
#include "../request_handler/IClientServerRequestHandler.h"
#include "../network/IConnection.h"
#include "../network/IServerSession.h"
#include "../network/IClientServerSession.h"

#include "../router/IRequestHandlerContext.h"


IResponseFactoryPtr CreateResponceFactory();
IServerSessionCreatorPtr CreateServerSessionCreator(const IServerReqHandlerCreatorPtr &handlerCreator);
IConnectionPtr CreateServerConnection(net::io_context &context, const IServerSessionCreatorPtr &creator, const IConfigPtr &config);

IClientServerSessionCreatorPtr CreateClientServerSessionCreator(const IClientServerReqHandlerCreatorPtr &handlerCreator);
IConnectionPtr CreateClientServerConnection(net::io_context &context, const IClientServerSessionCreatorPtr& sessionCreator, const IConfigPtr& config);
IRequestHandlerContextPtr CreateRequestsHandlerContext();