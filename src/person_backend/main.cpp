#include "../network_library/include/network/net.h"
#include "../base/include/config/config_creators.h"
#include "../base/include/logger/LoggerFactory.h"

#include <boost/smart_ptr/make_shared.hpp>

#include "utils/PersonsServerHandler.h"
#include "utils/PersonsGateway.h"
#include "database_manager/PersonsDA.h"
#include "person_facade/person_facade.h"


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    boost::shared_ptr<IConfig> config = createYAMLConfig(std::string(argv[1]));
    LoggerFactory::initLogger(config);

    PersonFacade::Instance()->init(createPersonsRepository(config, PersonBD));

    SetupRouter();

    auto respFactory = CreateResponceFactory();
    auto handlerCreator = boost::make_shared<ServerReqHandlerCreator<PersonsServerHandler>>(respFactory);
    auto sessionCreator = CreateServerSessionCreator(handlerCreator);

    net::io_context ioc;
    auto connection = CreateServerConnection(ioc, sessionCreator, config);
    connection->Run();

    return 0;
}