#pragma once
#include <string>

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
