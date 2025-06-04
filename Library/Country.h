#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Country {
public:
    int id;
    std::string name;

    Country() = default;
    Country(int id, const std::string& name) : id(id), name(name) {}

    void print() const;
};

inline void to_json(json& j, const Country& c) {
    j = json{ {"id", c.id}, {"name", c.name} };
}

inline void from_json(const json& j, Country& c) {
    j.at("id").get_to(c.id);
    j.at("name").get_to(c.name);
}
