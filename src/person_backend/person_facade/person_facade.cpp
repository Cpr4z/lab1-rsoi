#include "person_facade.h"

#include <boost/smart_ptr/make_shared.hpp>

#include "../../base/include/exceptions/logic_exceptions.h"
#include "../../base/include/exceptions/database_exceptions.h"

boost::shared_ptr<PersonFacade> PersonFacade::Instance()
{
    static boost::shared_ptr<PersonFacade> instance(new PersonFacade);
    return instance;
}

void PersonFacade::init(const IPersonsRepositoryPtr& repository)
{
    m_repository = repository;
}

void PersonFacade::addPerson(const PersonPostDTO& person)
{
    if (!m_repository)
    {
        throw NotInitializedException("not initializes repository");
    }
    m_repository->addPerson(person);
}

PersonDTO PersonFacade::getPerson(size_t id) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initialized");

    try
    {
        return m_repository->getPerson(id);
    }
    catch(const DatabaseNotFoundException& e)
    {
        throw PersonNotFoundException(e.what());
    }
}

PersonsDTO PersonFacade::getPersons() const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initialized");

    return m_repository->getPersons();
}

PersonDTO PersonFacade::patchPerson(size_t id, PersonPatchDTO& person) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initialized");

    return m_repository->patchPerson(id, person);
}

void PersonFacade::deletePerson(size_t id) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");

    m_repository->deletePerson(id);
}
