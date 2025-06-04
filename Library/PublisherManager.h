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
    void listPublishersWithoutEmail() const;
    void countPublishers() const;

    Publisher* findById(int id);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    const std::vector<Publisher>& getAll() const;
    const Publisher* findById(int id) const;

};
