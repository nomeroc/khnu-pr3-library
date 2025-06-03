#pragma once
#include <string>

class Book {
public:
    int id;
    std::string title;
    int genreId;
    int authorId;
    int countryId;
    float price;

    Book() = default;

    Book(int id, const std::string& title, int genreId, int authorId, int countryId, float price)
        : id(id), title(title), genreId(genreId), authorId(authorId), countryId(countryId), price(price) {
    }

    void print() const;
};
