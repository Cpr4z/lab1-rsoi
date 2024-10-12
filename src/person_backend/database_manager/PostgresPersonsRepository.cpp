#include "PostgresPersonsRepository.h"

#include <boost/smart_ptr/make_shared.hpp>

#include "../../base/include/config/base_constants.h"
#include "../../base/include/exceptions/database_exceptions.h"
#include "../../base/include/logger/LoggerFactory.h"

PostgresPersonsRepository::PostgresPersonsRepository(const IConfigPtr &config, const std::string &connectionSection)
{
    readConfig(config, connectionSection);
    connect();
    addPrepareStatement();
}

void PostgresPersonsRepository::addPerson(const PersonPostDTO &person)
{
    try
    {
        pqxx::work work(*m_connection);
        work.exec_prepared(m_requestsNames[WRITE], person.m_name, person.m_age, person.m_address, person.m_work);
        work.commit();
    }
    catch(std::exception& ex)
    {
        throw DatabaseExecutionException("can't execute this request");
    }
}

PersonsDTO PostgresPersonsRepository::getPersons()
{
    pqxx::result rows;
    try
    {
        pqxx::work work(*m_connection);
        rows = work.exec_prepared(m_requestsNames[READ_ALL]);
        work.commit();
    }
    catch(std::exception& ex)
    {
        throw DatabaseExecutionException("can't execute this request "+ std::string{ex.what()});
    }

    PersonsDTO persons;
    persons.reserve(rows.size());
    for (const auto& row : rows)
    {
        PersonDTO person{row["id"].as<size_t>(), row["name"].as<std::string>(),
                         row["address"].as<std::string>(), row["work"].as<std::string>(),
                         row["age"].as<size_t>()};
        persons.push_back(person);
    }

    return persons;
}

PersonDTO PostgresPersonsRepository::getPerson(size_t id)
{
    pqxx::result rows;
    try
    {
        pqxx::work work(*m_connection);
        rows = work.exec_prepared(m_requestsNames[READ_BY_ID], id);
        work.commit();
    }
    catch (std::exception& ex)
    {
        throw DatabaseExecutionException("can't execute this request " + std::string{ex.what()});
    }

    if (rows.empty())
    {
        throw DatabaseNotFoundException("person not found");
    }

    PersonDTO person{rows[0]["id"].as<size_t>(), rows[0]["name"].as<std::string>(), rows[0]["address"].as<std::string>(),
                     rows[0]["work"].as<std::string>(), rows[0]["age"].as<size_t>()};
    return person;
}

PersonDTO PostgresPersonsRepository::patchPerson(size_t id, const PersonPatchDTO &person)
{
    try
    {
        pqxx::work work(*m_connection);
        work.exec_prepared(m_requestsNames[PATCH], id, person.m_name, person.m_age, person.m_address, person.m_work);
        work.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException("can't execute this request " + std::string{ex.what()});
    }

    return getPerson(id);
}

void PostgresPersonsRepository::readConfig(const IConfigPtr &conf, const std::string &connectionSection)
{
    m_name = conf->GetStringField({connectionSection, AppLiterals::DbName});
    m_user = conf->GetStringField({connectionSection, AppLiterals::DbUser});
    m_userPassword = conf->GetStringField({connectionSection, AppLiterals::DbUserPassword});
    m_host = conf->GetStringField({connectionSection, AppLiterals::DbHost});
    m_port = conf->GetUintField({connectionSection, AppLiterals::DbPort});
}

void PostgresPersonsRepository::connect()
{
    std::string connectionCred = "dbname = " + m_name + " user = " + m_user + " password = " + m_userPassword +
                                 " host = " + m_host + " port = " + std::to_string(m_port);

    try
    {
        m_connection = boost::make_shared<pqxx::connection>(connectionCred.c_str());

        if (!m_connection->is_open())
        {
            throw DatabaseConnectException("Can't connect to " + m_name);
        }
        else
        {
            LoggerFactory::createLogger()->logInfo((std::string("Connected to database") + m_name).c_str());
        }
    }
    catch (std::exception& ex)
    {
        throw DatabaseConnectException("Can't connect to " + m_name + " " + ex.what());
    }
}

void PostgresPersonsRepository::deletePerson(size_t id)
{
    try
    {
        pqxx::work work(*m_connection);
        work.exec_prepared(m_requestsNames[DELETE], id);
        work.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException(ex.what());
    }
}

void PostgresPersonsRepository::addPrepareStatement()
{
    m_connection->prepare(m_requestsNames[READ_ALL], "SELECT * FROM T_Persons");
    m_connection->prepare(m_requestsNames[READ_BY_ID], "SELECT * FROM T_Persons WHERE id = $1");
    m_connection->prepare(m_requestsNames[DELETE], "DELETE FROM T_Persons WHERE id = $id");
    m_connection->prepare(m_requestsNames[WRITE], "INSERT INTO T_Persons (name, age, address, work) VALUES ($1, $2, $3, $4)");
    m_connection->prepare(m_requestsNames[PATCH], "UPDATE T_Persons name=$2, age=$3, address=$4, work=$5 WHERE id=$1");

}
