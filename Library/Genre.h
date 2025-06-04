#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Genre {
public:
    int id;
    std::string name;

    Genre() = default;
    Genre(int id, const std::string& name) : id(id), name(name) {}

    void print() const;
};

inline void to_json(json& j, const Genre& g) {
    j = json{ {"id", g.id}, {"name", g.name} };
}

inline void from_json(const json& j, Genre& g) {
    j.at("id").get_to(g.id);
    j.at("name").get_to(g.name);
}
