#include "PersonDTO.h"

#include <nlohmann/json.hpp>
#include "../../base/include/exceptions/server_exceptions.h"


void PersonDTO::fromJSON(const std::string& json) {
    try {
        nlohmann::json obj = nlohmann::json::parse(json);

        m_id = obj.at("id").get<uint64_t>();
        m_name = obj.at("name").get<std::string>();
        m_address = obj.at("address").get<std::string>();
        m_work = obj.at("work").get<std::string>();
        m_age = obj.at("age").get<uint64_t>();
    } catch (const nlohmann::json::exception& e) {
        throw JsonParserException("Can't parse PersonDTO object: " + std::string(e.what()));
    }
}

nlohmann::json getJSON(const PersonDTO& person)
{
    nlohmann::json root;

    root["id"] = person.m_id;
    root["name"] = person.m_name;
    root["address"] = person.m_address;
    root["work"] = person.m_work;
    root["age"] = person.m_age;

    return root;
}

std::string PersonDTO::toJSON() const {
    nlohmann::json root = getJSON(*this);
    return root.dump();
}

std::string ToJSON(const PersonsDTO& persons)
{
    nlohmann::json arr = nlohmann::json::array();

    for (const auto& person : persons) {
        arr.push_back(getJSON(person));
    }

    return arr.dump();
}
