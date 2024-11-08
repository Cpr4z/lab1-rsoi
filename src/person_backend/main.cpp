#include <iostream>
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
    std::cout << "Persons App was started" << std::endl;

    boost::shared_ptr<IConfig> config = createYAMLConfig(std::string(argv[0]));
    LoggerFactory::initLogger(config);

    std::cout << "Config is loaded" << std::endl;

    PersonFacade::Instance()->init(createPersonsRepository(config, PersonBD));

    SetupRouter();

    auto respFactory = CreateResponceFactory();
    auto handlerCreator = boost::make_shared<ServerReqHandlerCreator<PersonsServerHandler>>(respFactory);
    auto sessionCreator = CreateServerSessionCreator(handlerCreator);

    net::io_context ioc;
    auto connection = CreateServerConnection(ioc, sessionCreator, config);
    std::cout << "Starting server event loop..." << std::endl;
    connection->Run();
    std::cout << "Server event loop ended." << std::endl;

    return 0;
}