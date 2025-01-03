#pragma once

#include "PersonsRepositoryMock.h"
#include <gtest/gtest.h>

class PersonsFacadeTests : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

public:
    boost::shared_ptr<PersonsRepositoryMock> m_personsDb;
};