#pragma once
#include <vector>
#include "Book.h"
#include "IDatabaseEntity.h"
#include "AuthorManager.h"
#include "GenreManager.h"


class BookManager : public IDatabaseEntity {
private:
    std::vector<Book> books;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;
    void listBooksByPriceRange(float minPrice, float maxPrice) const;
    void listBooksByAuthorLastName(const std::string& lastName, const AuthorManager& authorManager) const;
    void listGenresByAuthorId(int authorId, const GenreManager& genreManager, const AuthorManager& authorManager) const;
    void adjustPricesByPercentage(float percentage);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    const std::vector<Book>& getAll() const;
};
