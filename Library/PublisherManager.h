#pragma once
#include <vector>
#include "Publisher.h"
#include "IDatabaseEntity.h"

class PublisherManager : public IDatabaseEntity {
private:
    std::vector<Publisher> publishers;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;

    Publisher* findById(int id);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
