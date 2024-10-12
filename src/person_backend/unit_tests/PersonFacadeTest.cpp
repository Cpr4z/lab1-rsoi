#include "PersonFacadeTest.h"

#include <boost/smart_ptr/make_shared.hpp>
#include "../person_facade/person_facade.h"

using ::testing::_;
using ::testing::Return;

void PersonsFacadeTests::SetUp()
{
    m_personsDb = boost::make_shared<PersonsRepositoryMock>();

    PersonFacade::Instance()->init(m_personsDb);
}

void PersonsFacadeTests::TearDown()
{
}

TEST_F(PersonsFacadeTests, create_person)
{
PersonPostDTO person{"name", "address", "work", 1};
EXPECT_CALL(*m_personsDb, addPerson(person)).Times(1);

PersonFacade::Instance()->addPerson(person);
}

TEST_F(PersonsFacadeTests, read_person)
{
PersonDTO person{10, "name", "address", "work", 1};
EXPECT_CALL(*m_personsDb, getPerson(person.m_id)).Times(1).WillRepeatedly(Return(person));

PersonDTO res = PersonFacade::Instance()->getPerson(person.m_id);

EXPECT_TRUE(res == person);
}

TEST_F(PersonsFacadeTests, read_persons) {
    PersonsDTO persons({{10, "name",   "address",   "work",   1},
                        {11, "name 1", "address 1", "work 1", 10}});
    EXPECT_CALL(*m_personsDb, getPersons()).Times(1).WillRepeatedly(Return(persons));

    PersonsDTO res = PersonFacade::Instance()->getPersons();

    EXPECT_TRUE(res == persons);
}


TEST_F(PersonsFacadeTests, delete_person)
{
size_t personId = 1;
EXPECT_CALL(*m_personsDb, deletePerson(personId)).Times(personId);
PersonFacade::Instance()->deletePerson(personId);
}