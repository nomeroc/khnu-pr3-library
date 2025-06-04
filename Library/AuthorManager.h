#pragma once
#include <vector>
#include "Author.h"
#include "IDatabaseEntity.h"
#include "CountryManager.h"

class AuthorManager : public IDatabaseEntity {
private:
    std::vector<Author> authors;


public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;
    void listAuthorsSortedByLastName() const;
    const std::vector<Author>& getAll() const;
    void countAuthorsPerCountry(const CountryManager& countryManager) const;

    // Optional helper
    const Author* findById(int id) const;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
