#pragma once
#include <string>

class Genre {
public:
    int id;
    std::string name;

    Genre() = default;

    Genre(int id, const std::string& name) : id(id), name(name) {}

    void print() const;
};
