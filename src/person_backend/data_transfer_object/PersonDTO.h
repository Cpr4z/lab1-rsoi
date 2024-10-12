#pragma once

#include <vector>
#include <string>
#include <compare>
#include <memory>

class PersonDTO {
public:
    void fromJSON(const std::string& json);
    [[nodiscard]] std::string toJSON() const;

    auto operator<=>(const PersonDTO&) const = default;

    size_t m_id;
    std::string m_name;
    std::string m_address;
    std::string m_work;
    size_t m_age;
};

using PersonsDTO = std::vector<PersonDTO>;

std::string ToJSON(const PersonsDTO& persons);