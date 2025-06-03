#pragma once
#include <vector>
#include "Book.h"
#include "IDatabaseEntity.h"

class BookManager : public IDatabaseEntity {
private:
    std::vector<Book> books;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    const std::vector<Book>& getAll() const;
};
