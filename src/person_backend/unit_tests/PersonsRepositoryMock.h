#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../database_manager/IPersonsRepository.h"

class PersonsRepositoryMock : public IPersonsRepository
{
public:
    MOCK_METHOD(void, addPerson, (const PersonPostDTO& person), (override));
    MOCK_METHOD(PersonsDTO, getPersons, (), (override));
    MOCK_METHOD(PersonDTO, getPerson, (size_t id), (override));
    MOCK_METHOD(PersonDTO, patchPerson, (size_t id, const PersonPatchDTO& person), (override));
    MOCK_METHOD(void, deletePerson, (size_t id), (override));
};