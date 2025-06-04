#pragma once
#include <vector>
#include "Country.h"
#include "IDatabaseEntity.h"

class CountryManager : public IDatabaseEntity {
private:
    std::vector<Country> countries;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;
    const std::vector<Country>& getAll() const;

    Country* findById(int id);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};