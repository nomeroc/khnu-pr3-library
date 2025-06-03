#include "GenreManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

void GenreManager::add() {
    int id;
    std::string name;

    std::cout << "Enter genre ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter genre name: ";
    std::getline(std::cin, name);

    genres.emplace_back(id, name);
    std::cout << "Genre added successfully.\n";
}

void GenreManager::remove() {
    int id;
    std::cout << "Enter genre ID to remove: ";
    std::cin >> id;

    auto it = std::remove_if(genres.begin(), genres.end(), [id](const Genre& g) {
        return g.id == id;
        });

    if (it != genres.end()) {
        genres.erase(it, genres.end());
        std::cout << "Genre removed.\n";
    }
    else {
        std::cout << "Genre not found.\n";
    }
}

void GenreManager::update() {
    int id;
    std::cout << "Enter genre ID to update: ";
    std::cin >> id;
    std::cin.ignore();

    for (auto& genre : genres) {
        if (genre.id == id) {
            std::cout << "Enter new genre name: ";
            std::getline(std::cin, genre.name);

            std::cout << "Genre updated.\n";
            return;
        }
    }

    std::cout << "Genre not found.\n";
}

void GenreManager::listAll() const {
    if (genres.empty()) {
        std::cout << "No genres found.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(30) << "Genre Name"
        << "\n"
        << std::string(36, '-') << "\n";

    for (const auto& genre : genres) {
        genre.print();
    }
}


void GenreManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& genre : genres) {
        out << genre.id << ";" << genre.name << "\n";
    }

    out.close();
    std::cout << "Genres saved to " << filename << "\n";
}

void GenreManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty genre list.\n";
        return;
    }

    genres.clear();

    std::string line, token;
    int id;
    std::string name;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::getline(ss, token, ';'); id = std::stoi(token);
        std::getline(ss, name, ';');

        genres.emplace_back(id, name);
    }

    in.close();
    std::cout << "Genres loaded from " << filename << "\n";
}

Genre* GenreManager::findById(int id) {
    for (auto& genre : genres) {
        if (genre.id == id) {
            return &genre;
        }
    }
    return nullptr;
}
