#pragma once

#include <string>
#include <compare>

class PersonPostDTO
{
public:
    void fromJSON(const std::string& json);
    [[nodiscard]] std::string toJSON() const;

    std::string m_name;
    std::string m_address;
    std::string m_work;
    size_t m_age;

    auto operator <=>(const PersonPostDTO&) const = default;
};