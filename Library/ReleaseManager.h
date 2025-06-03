#pragma once
#include <vector>
#include "Release.h"
#include "IDatabaseEntity.h"

class ReleaseManager : public IDatabaseEntity {
private:
    std::vector<Release> releases;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;

    Release* findByBatchId(int batchId);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
