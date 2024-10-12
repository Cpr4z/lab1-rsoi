#include "PersonPostDTO.h"

#include <nlohmann/json.hpp>

//#include <exceptions/server_exceptions.h>

#include "../../base/include/exceptions/server_exceptions.h"

void PersonPostDTO::fromJSON(const std::string &json) {
    try {
        nlohmann::json obj = nlohmann::json::parse(json);

        m_name = obj.at("name").get<std::string>();
        m_address = obj.at("address").get<std::string>();
        m_work = obj.at("work").get<std::string>();
        m_age = obj.at("age").get<uint64_t>();
    } catch (const nlohmann::json::exception& e) {
        throw JsonParserException("Can't parse PersonPostDTO object: " + std::string(e.what()));
    }
}

std::string PersonPostDTO::toJSON() const {
    nlohmann::json value;

    value["name"] = m_name;
    value["address"] = m_address;
    value["work"] = m_work;
    value["age"] = m_age;

    return value.dump();
}
