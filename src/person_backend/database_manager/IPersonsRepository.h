#pragma once

#include <boost/shared_ptr.hpp>

#include "../data_transfer_object/PersonDTO.h"
#include "../data_transfer_object/PersonPostDTO.h"
#include "../data_transfer_object/PersonPatchDTO.h"

class IPersonsRepository
{
public:
    virtual ~IPersonsRepository() = default;

    virtual void addPerson(const PersonPostDTO& person) = 0;
    virtual PersonsDTO getPersons() = 0;
    virtual PersonDTO getPerson(size_t id) = 0;
    virtual PersonDTO patchPerson(size_t id, const PersonPatchDTO& person) = 0;
    virtual void deletePerson(size_t id) = 0;
};

using IPersonsRepositoryPtr = boost::shared_ptr<IPersonsRepository>;