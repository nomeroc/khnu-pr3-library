#include "ReleaseManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

void ReleaseManager::add() {
    int batchId, bookId, publisherId, copies;
    std::string date;

    std::cout << "Enter batch ID: ";
    std::cin >> batchId;

    std::cout << "Enter book ID: ";
    std::cin >> bookId;

    std::cout << "Enter publisher ID: ";
    std::cin >> publisherId;

    std::cout << "Enter number of copies: ";
    std::cin >> copies;
    std::cin.ignore();

    std::cout << "Enter release date (e.g., 2023-11-15): ";
    std::getline(std::cin, date);

    releases.emplace_back(batchId, bookId, publisherId, copies, date);
    std::cout << "Release added successfully.\n";
}

void ReleaseManager::remove() {
    int batchId;
    std::cout << "Enter batch ID to remove: ";
    std::cin >> batchId;

    auto it = std::remove_if(releases.begin(), releases.end(), [batchId](const Release& r) {
        return r.batchId == batchId;
        });

    if (it != releases.end()) {
        releases.erase(it, releases.end());
        std::cout << "Release removed.\n";
    }
    else {
        std::cout << "Release not found.\n";
    }
}

void ReleaseManager::update() {
    int batchId;
    std::cout << "Enter batch ID to update: ";
    std::cin >> batchId;
    std::cin.ignore();

    for (auto& release : releases) {
        if (release.batchId == batchId) {
            std::cout << "Enter new book ID: ";
            std::cin >> release.bookId;

            std::cout << "Enter new publisher ID: ";
            std::cin >> release.publisherId;

            std::cout << "Enter new number of copies: ";
            std::cin >> release.copies;
            std::cin.ignore();

            std::cout << "Enter new release date: ";
            std::getline(std::cin, release.releaseDate);

            std::cout << "Release updated.\n";
            return;
        }
    }

    std::cout << "Release not found.\n";
}

void ReleaseManager::listAll() const {
    if (releases.empty()) {
        std::cout << "No releases found.\n";
        return;
    }

    std::cout << std::left
        << std::setw(10) << "Batch ID"
        << std::setw(10) << "Book ID"
        << std::setw(15) << "Publisher ID"
        << std::setw(10) << "Copies"
        << std::setw(15) << "Date"
        << "\n"
        << std::string(60, '-') << "\n";

    for (const auto& release : releases) {
        release.print();
    }
}


void ReleaseManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& release : releases) {
        out << release.batchId << ";"
            << release.bookId << ";"
            << release.publisherId << ";"
            << release.copies << ";"
            << release.releaseDate << "\n";
    }

    out.close();
    std::cout << "Releases saved to " << filename << "\n";
}

void ReleaseManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty release list.\n";
        return;
    }

    releases.clear();

    std::string line, token;
    int batchId, bookId, publisherId, copies;
    std::string releaseDate;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::getline(ss, token, ';'); batchId = std::stoi(token);
        std::getline(ss, token, ';'); bookId = std::stoi(token);
        std::getline(ss, token, ';'); publisherId = std::stoi(token);
        std::getline(ss, token, ';'); copies = std::stoi(token);
        std::getline(ss, releaseDate, ';');

        releases.emplace_back(batchId, bookId, publisherId, copies, releaseDate);
    }

    in.close();
    std::cout << "Releases loaded from " << filename << "\n";
}

Release* ReleaseManager::findByBatchId(int batchId) {
    for (auto& release : releases) {
        if (release.batchId == batchId) {
            return &release;
        }
    }
    return nullptr;
}