#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Author {
public:
    int id;
    std::string firstName;
    std::string lastName;
    std::string middleName;
    int countryId;

    Author() = default;

    Author(int id, const std::string& firstName, const std::string& lastName,
        const std::string& middleName, int countryId)
        : id(id), firstName(firstName), lastName(lastName), middleName(middleName), countryId(countryId) {
    }

    void print() const;
};

// ✅ JSON support

inline void to_json(json& j, const Author& a) {
    j = json{
        {"id", a.id},
        {"firstName", a.firstName},
        {"lastName", a.lastName},
        {"middleName", a.middleName},
        {"countryId", a.countryId}
    };
}

inline void from_json(const json& j, Author& a) {
    j.at("id").get_to(a.id);
    j.at("firstName").get_to(a.firstName);
    j.at("lastName").get_to(a.lastName);
    j.at("middleName").get_to(a.middleName);
    j.at("countryId").get_to(a.countryId);
}
