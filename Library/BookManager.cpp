#include "BookManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "AuthorManager.h"
#include "json.hpp"
#include <set>
#include <iomanip>

using json = nlohmann::json;

void BookManager::add() {
    int id, genreId, authorId, countryId;
    float price;
    std::string title;

    std::cout << "Enter book ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter title: ";
    std::getline(std::cin, title);

    std::cout << "Enter genre ID: ";
    std::cin >> genreId;

    std::cout << "Enter author ID: ";
    std::cin >> authorId;

    std::cout << "Enter country ID: ";
    std::cin >> countryId;

    std::cout << "Enter price: ";
    std::cin >> price;

    books.emplace_back(id, title, genreId, authorId, countryId, price);
    std::cout << "Book added successfully.\n";
}

void BookManager::remove() {
    int id;
    std::cout << "Enter book ID to remove: ";
    std::cin >> id;

    auto it = std::remove_if(books.begin(), books.end(), [id](const Book& b) {
        return b.id == id;
        });

    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Book removed.\n";
    }
    else {
        std::cout << "Book not found.\n";
    }
}

void BookManager::update() {
    int id;
    std::cout << "Enter book ID to update: ";
    std::cin >> id;

    for (auto& book : books) {
        if (book.id == id) {
            std::cout << "Enter new title: ";
            std::cin.ignore();
            std::getline(std::cin, book.title);

            std::cout << "Enter new price: ";
            std::cin >> book.price;

            std::cout << "Book updated.\n";
            return;
        }
    }
    std::cout << "Book not found.\n";
}

void BookManager::listAll() const {
    if (books.empty()) {
        std::cout << "No books found.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(25) << "Title"
        << std::setw(10) << "Genre"
        << std::setw(10) << "Author"
        << std::setw(10) << "Country"
        << std::setw(10) << "Price"
        << "\n";

    std::cout << std::string(71, '-') << "\n";

    for (const auto& book : books) {
        book.print();
    }
}

void BookManager::listBooksByPriceRange(float minPrice, float maxPrice) const {
    bool found = false;

    std::cout << "\nBooks priced between " << minPrice << " and " << maxPrice << ":\n";
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(25) << "Title"
        << std::setw(10) << "Genre"
        << std::setw(10) << "Author"
        << std::setw(10) << "Country"
        << std::setw(10) << "Price"
        << "\n"
        << std::string(46, '-') << "\n";

    for (const auto& book : books) {
        if (book.price >= minPrice && book.price <= maxPrice) {
            book.print(); // Make sure Book::print() shows title and price
            found = true;
        }
    }

    if (!found) std::cout << "No books in this price range.\n";
}

void BookManager::listBooksByAuthorLastName(const std::string& lastName, const AuthorManager& authorManager) const {
    std::vector<int> matchingAuthorIds;

    for (const auto& author : authorManager.getAll()) {
        if (author.lastName == lastName) {
            matchingAuthorIds.push_back(author.id);
        }
    }

    if (matchingAuthorIds.empty()) {
        std::cout << "No authors found with last name: " << lastName << "\n";
        return;
    }

    std::cout << "\nBooks by authors with last name: " << lastName << "\n";
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(25) << "Title"
        << std::setw(10) << "Genre"
        << std::setw(10) << "Author"
        << std::setw(10) << "Country"
        << std::setw(10) << "Price"
        << "\n"
        << std::string(56, '-') << "\n";

    bool found = false;
    for (const auto& book : books) {
        if (std::find(matchingAuthorIds.begin(), matchingAuthorIds.end(), book.authorId) != matchingAuthorIds.end()) {
            book.print();
            found = true;
        }
    }

    if (!found)
        std::cout << "No books found for author " << lastName << ".\n";
}

void BookManager::listGenresByAuthorId(int authorId, const GenreManager& genreManager, const AuthorManager& authorManager) const {
    std::set<int> genreIds;

    for (const auto& book : books) {
        if (book.authorId == authorId) {
            genreIds.insert(book.genreId);
        }
    }

    const Author* author = authorManager.findById(authorId);
    std::string authorName = (author != nullptr)
        ? (author->lastName + " " + author->firstName + " " + author->middleName)
        : "(Unknown Author)";

    std::cout << "\nGenres written by " << authorName << " (ID: " << authorId << "):\n";
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(30) << "Genre"
        << "\n"
        << std::string(36, '-') << "\n";

    for (const auto& genre : genreManager.getAll()) {
        if (genreIds.count(genre.id)) {
            std::cout << std::left
                << std::setw(6) << genre.id
                << std::setw(30) << genre.name
                << "\n";
        }
    }
}

void BookManager::adjustPricesByPercentage(float percentage) {
    float factor = 1.0f + (percentage / 100.0f);

    std::cout << "\nAdjusting all book prices by " << percentage << "%\n";
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(30) << "Title"
        << std::setw(12) << "Old Price"
        << std::setw(12) << "New Price"
        << "\n"
        << std::string(60, '-') << "\n";

    for (auto& book : books) {
        float oldPrice = book.price;
        book.price *= factor;
        float newPrice = book.price;

        std::cout << std::left
            << std::setw(6) << book.id
            << std::setw(30) << book.title
            << std::setw(12) << std::fixed << std::setprecision(2) << oldPrice
            << std::setw(12) << std::fixed << std::setprecision(2) << newPrice
            << "\n";
    }

    std::cout << "\nPrice adjustment completed.\n";
}


void BookManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    json j = books;
    out << j.dump(4);  // Pretty print with 4-space indent
    out.close();

    std::cout << "Books saved to " << filename << "\n";
}


void BookManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty book list.\n";
        return;
    }

    json j;
    in >> j;
    books = j.get<std::vector<Book>>();
    in.close();

    std::cout << "Books loaded from " << filename << "\n";
}


const std::vector<Book>& BookManager::getAll() const {
    return books;
}
