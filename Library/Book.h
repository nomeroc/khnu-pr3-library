#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

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

inline void to_json(json& j, const Book& b) {
    j = json{
        {"id", b.id},
        {"title", b.title},
        {"genreId", b.genreId},
        {"authorId", b.authorId},
        {"countryId", b.countryId},
        {"price", b.price}
    };
}

inline void from_json(const json& j, Book& b) {
    j.at("id").get_to(b.id);
    j.at("title").get_to(b.title);
    j.at("genreId").get_to(b.genreId);
    j.at("authorId").get_to(b.authorId);
    j.at("countryId").get_to(b.countryId);
    j.at("price").get_to(b.price);
}
