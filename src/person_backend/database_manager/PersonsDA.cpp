#include "PersonsDA.h"
#include "PostgresPersonsRepository.h"
#include <boost/smart_ptr/make_shared.hpp>

IPersonsRepositoryPtr createPersonsRepository(const IConfigPtr& config, const std::string& connectionSection)
{
    return boost::make_shared<PostgresPersonsRepository>(config, connectionSection);
}