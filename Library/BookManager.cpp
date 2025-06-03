#include "BookManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

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

void BookManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& book : books) {
        out << book.id << ";"
            << book.title << ";"
            << book.genreId << ";"
            << book.authorId << ";"
            << book.countryId << ";"
            << book.price << "\n";
    }

    out.close();
    std::cout << "Books saved to " << filename << "\n";
}

void BookManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty book list.\n";
        return;
    }

    books.clear();

    int id, genreId, authorId, countryId;
    float price;
    std::string title, line;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ';'); id = std::stoi(token);
        std::getline(ss, title, ';');
        std::getline(ss, token, ';'); genreId = std::stoi(token);
        std::getline(ss, token, ';'); authorId = std::stoi(token);
        std::getline(ss, token, ';'); countryId = std::stoi(token);
        std::getline(ss, token, ';'); price = std::stof(token);

        books.emplace_back(id, title, genreId, authorId, countryId, price);
    }

    in.close();
    std::cout << "Books loaded from " << filename << "\n";
}

const std::vector<Book>& BookManager::getAll() const {
    return books;
}
