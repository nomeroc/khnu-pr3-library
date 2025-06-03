#pragma once
#include <string>

class Country {
public:
    int id;
    std::string name;

    Country() = default;

    Country(int id, const std::string& name) : id(id), name(name) {}

    void print() const;
};
