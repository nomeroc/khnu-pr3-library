#include "AuthorManager.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>

void AuthorManager::add() {
    int id, countryId;
    std::string firstName, lastName, middleName;

    std::cout << "Enter author ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);

    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);

    std::cout << "Enter middle name: ";
    std::getline(std::cin, middleName);

    std::cout << "Enter country ID: ";
    std::cin >> countryId;

    authors.emplace_back(id, firstName, lastName, middleName, countryId);
    std::cout << "Author added successfully.\n";
}

void AuthorManager::remove() {
    int id;
    std::cout << "Enter author ID to remove: ";
    std::cin >> id;

    auto it = std::remove_if(authors.begin(), authors.end(), [id](const Author& a) {
        return a.id == id;
        });

    if (it != authors.end()) {
        authors.erase(it, authors.end());
        std::cout << "Author removed.\n";
    }
    else {
        std::cout << "Author not found.\n";
    }
}

void AuthorManager::update() {
    int id;
    std::cout << "Enter author ID to update: ";
    std::cin >> id;
    std::cin.ignore();

    for (auto& author : authors) {
        if (author.id == id) {
            std::cout << "Enter new first name: ";
            std::getline(std::cin, author.firstName);

            std::cout << "Enter new last name: ";
            std::getline(std::cin, author.lastName);

            std::cout << "Enter new middle name: ";
            std::getline(std::cin, author.middleName);

            std::cout << "Enter new country ID: ";
            std::cin >> author.countryId;

            std::cout << "Author updated.\n";
            return;
        }
    }

    std::cout << "Author not found.\n";
}

void AuthorManager::listAll() const {
    if (authors.empty()) {
        std::cout << "No authors found.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(15) << "Last Name"
        << std::setw(15) << "First Name"
        << std::setw(15) << "Middle Name"
        << std::setw(10) << "Country"
        << "\n"
        << std::string(61, '-') << "\n";

    for (const auto& author : authors) {
        author.print();
    }
}

void AuthorManager::listAuthorsSortedByLastName() const {
    if (authors.empty()) {
        std::cout << "No authors found.\n";
        return;
    }

    std::vector<Author> sorted = authors;

    std::sort(sorted.begin(), sorted.end(), [](const Author& a, const Author& b) {
        return a.lastName < b.lastName;
        });

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(15) << "Last Name"
        << std::setw(15) << "First Name"
        << std::setw(15) << "Middle Name"
        << std::setw(10) << "Country"
        << "\n"
        << std::string(61, '-') << "\n";

    for (const auto& author : sorted) {
        author.print();
    }
}

void AuthorManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& author : authors) {
        out << author.id << ";"
            << author.firstName << ";"
            << author.lastName << ";"
            << author.middleName << ";"
            << author.countryId << "\n";
    }

    out.close();
    std::cout << "Authors saved to " << filename << "\n";
}

void AuthorManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty author list.\n";
        return;
    }

    authors.clear();

    std::string line, token;
    int id, countryId;
    std::string firstName, lastName, middleName;

    while (std::getline(in, line)) {
        std::stringstream ss(line);

        std::getline(ss, token, ';'); id = std::stoi(token);
        std::getline(ss, firstName, ';');
        std::getline(ss, lastName, ';');
        std::getline(ss, middleName, ';');
        std::getline(ss, token, ';'); countryId = std::stoi(token);

        authors.emplace_back(id, firstName, lastName, middleName, countryId);
    }

    in.close();
    std::cout << "Authors loaded from " << filename << "\n";
}

const std::vector<Author>& AuthorManager::getAll() const {
    return authors;
}

Author* AuthorManager::findById(int id) {
    for (auto& author : authors) {
        if (author.id == id) {
            return &author;
        }
    }
    return nullptr;
}
