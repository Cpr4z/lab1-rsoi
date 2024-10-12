#pragma once

#include <boost/shared_ptr.hpp>

#include "../data_transfer_object/PersonDTO.h"
#include "../data_transfer_object/PersonPostDTO.h"
#include "../data_transfer_object/PersonPatchDTO.h"
#include "../database_manager/IPersonsRepository.h"

class PersonFacade
{
public:
    static boost::shared_ptr<PersonFacade> Instance();
    void init(const IPersonsRepositoryPtr& repository);

    void addPerson(const PersonPostDTO& person);
    [[nodiscard]] PersonDTO getPerson(size_t id) const;
    [[nodiscard]] PersonsDTO getPersons() const;
    [[nodiscard]] PersonDTO patchPerson(size_t id, PersonPatchDTO& person) const;
    void deletePerson(size_t id)const;

private:
    PersonFacade() = default;
    IPersonsRepositoryPtr m_repository;

};


