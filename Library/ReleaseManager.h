#pragma once
#include <vector>
#include "Release.h"
#include "IDatabaseEntity.h"
#include "PublisherManager.h"
#include "BookManager.h"

class ReleaseManager : public IDatabaseEntity {
private:
    std::vector<Release> releases;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;
    void countCopiesByPublisherInYear(const PublisherManager& publisherManager, const std::string& year) const;
    void showBookWithMaxCopiesInYear(const BookManager& bookManager, const std::string& year) const;
    void countBooksPerPublisher(const PublisherManager& publisherManager) const;

    Release* findByBatchId(int batchId);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
