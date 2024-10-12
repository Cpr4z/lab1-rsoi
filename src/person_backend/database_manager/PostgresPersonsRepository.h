#pragma once

#include <map>
#include <pqxx/pqxx>

#include "../../base/include/config/IConfig.h"
#include "IPersonsRepository.h"

class PostgresPersonsRepository
        : public IPersonsRepository
{
public:
    PostgresPersonsRepository(const IConfigPtr& config, const std::string& connection);
    virtual void addPerson(const PersonPostDTO& person) override;
    virtual PersonsDTO getPersons() override;
    virtual PersonDTO getPerson(size_t id) override;
    virtual PersonDTO patchPerson(size_t id, const PersonPatchDTO& person) override;
    virtual void deletePerson(size_t id) override;

private:
    void readConfig(const IConfigPtr& conf, const std::string& connection);

    void connect();
    void addPrepareStatement();

    boost::shared_ptr<pqxx::connection> m_connection;

    std::string m_name;
    std::string m_user;
    std::string m_userPassword;
    std::string m_host;
    size_t m_port;

    enum prepareRequest : size_t {
        WRITE,
        READ_BY_ID,
        READ_ALL,
        PATCH,
        DELETE
    };

    std::map<prepareRequest, std::string> m_requestsNames = {
            {WRITE, "add_person"},
            {READ_BY_ID, "get_person_by_id"},
            {READ_ALL, "get_all_persons"},
            {PATCH, "patch_person"},
            {DELETE, "delete_person_by_id"}
    };
};