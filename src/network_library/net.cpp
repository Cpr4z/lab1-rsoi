#include <network/net.h>

#include "base/BeastResponseFactory.h"
#include "connections/server_connection.h"
#include "connections/client_server_connection.h"
#include "sessions/http_session.h"
#include "sessions/http_client_server_session.h"
#include "router/RequestHandlerContext.h"
#include <boost/smart_ptr/make_shared.hpp>

IResponseFactoryPtr CreateResponceFactory()
{
    return boost::make_shared<BeastResponseFactory>();
}

IServerSessionCreatorPtr CreateServerSessionCreator(const IServerReqHandlerCreatorPtr &handlerCreator)
{
    return boost::make_shared<HttpServerSessionCreator>(handlerCreator);
}

IClientServerSessionCreatorPtr CreateClientServerSessionCreator(const IClientServerReqHandlerCreatorPtr &handlerCreator)
{
    return boost::make_shared<HttpClientServerSessionCreator>(handlerCreator);
}

IConnectionPtr CreateClientServerConnection(net::io_context &context,
                                            const IClientServerSessionCreatorPtr &sessionCreator,
                                            const IConfigPtr &config)
{
    return boost::make_shared<ClientServerConnection>(context, sessionCreator, config);
}

IRequestHandlerContextPtr CreateRequestsHandlerContext()
{
    return boost::make_shared<RequestsHandlerContext>();
}

IConnectionPtr CreateServerConnection(net::io_context &context, const IServerSessionCreatorPtr &creator,
                                      const IConfigPtr &config)
{
    return boost::make_shared<ServerConnection>(context, creator, config);
}