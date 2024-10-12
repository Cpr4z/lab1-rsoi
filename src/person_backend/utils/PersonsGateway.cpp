#include "PersonsGateway.h"

//#include <exceptions/logic_exceptions.h>
#include "../../base/include/exceptions/logic_exceptions.h"
//#include <router/router.h>
#include "../../network_library/include/router/router.h"
//#include <logger/LoggerFactory.h>
#include "../../base/include/logger/LoggerFactory.h"

#include "../data_transfer_object/PersonDTO.h"


#include "../person_facade/person_facade.h"

void Check(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
        return resp->SetStatus(network::CODE_503);

    resp->SetBody(params[0]);
    resp->SetStatus(network::CODE_200);
}

void Health(const IResponsePtr &resp, const IRequestPtr &)
{
    resp->SetStatus(network::CODE_200);
}

void GetPerson(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
    {
        LoggerFactory::createLogger()->logError("get person incorrect params count");
        resp->SetStatus(network::CODE_503);
        return;
    }

    size_t personId = std::stoul(params[0]);

    try
    {
        PersonDTO person = PersonFacade::Instance()->getPerson(personId);
        resp->SetBody(person.toJSON());
        resp->SetStatus(network::CODE_200);
    }
    catch (const PersonNotFoundException &e)
    {
        LoggerFactory::createLogger()->logError((std::string("Person not found: ") + std::to_string(personId)).c_str());
        resp->SetBody("{\"message\": \"not found\"}");
        resp->SetStatus(network::CODE_404);
    }
}

void PatchPerson(const IResponsePtr &resp, const IRequestPtr &request, const std::vector<std::string> &params)
{
    if (params.size() != 1)
    {
        LoggerFactory::createLogger()->logError("patch person incorrect params count");
        resp->SetStatus(network::CODE_503);
        return;
    }

    size_t personId = std::stoul(params[0]);
    PersonPatchDTO person;
    person.fromJSON(request->GetBody());

    PersonDTO res = PersonFacade::Instance()->patchPerson(personId, person);

    resp->SetStatus(network::CODE_200);
    resp->SetBody(res.toJSON());
}

void DeletePerson(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
    {
        LoggerFactory::createLogger()->logError("delete person incorrect params count");
        resp->SetStatus(network::CODE_503);
        return;
    }

    size_t personId = std::stoul(params[0]);

    PersonFacade::Instance()->deletePerson(personId);
    resp->SetStatus(network::CODE_204);
}

void GetPersons(const IResponsePtr &resp, const IRequestPtr &)
{
    PersonsDTO persons = PersonFacade::Instance()->getPersons();

    resp->SetBody(ToJSON(persons));
    resp->SetStatus(network::CODE_200);
}

void AddPerson(const IResponsePtr &resp, const IRequestPtr &request)
{
    PersonPostDTO person;
    person.fromJSON(request->GetBody());

    PersonFacade::Instance()->addPerson(person);

    resp->SetStatus(network::CODE_201);
}

void SetupRouter()
{
    RequestsRouter::Instanse()->AddStaticEndpoint({"/health", network::GET}, Health);
    RequestsRouter::Instanse()->AddStaticEndpoint({"/api/v1/persons", network::GET}, GetPersons);
    RequestsRouter::Instanse()->AddStaticEndpoint({"/api/v1/persons", network::POST}, AddPerson);
    RequestsRouter::Instanse()->AddDynamicEndpoint({std::regex("/api/v1/persons/([0-9\\-]+)"), network::GET}, GetPerson);
    RequestsRouter::Instanse()->AddDynamicEndpoint({std::regex("/api/v1/persons/([0-9\\-]+)"), network::DELETE}, DeletePerson);
    RequestsRouter::Instanse()->AddDynamicEndpoint({std::regex("/api/v1/persons/([0-9\\-]+)"), network::PATCH}, PatchPerson);
}