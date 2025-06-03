#include "CountryManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

void CountryManager::add() {
    int id;
    std::string name;

    std::cout << "Enter country ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter country name: ";
    std::getline(std::cin, name);

    countries.emplace_back(id, name);
    std::cout << "Country added successfully.\n";
}

void CountryManager::remove() {
    int id;
    std::cout << "Enter country ID to remove: ";
    std::cin >> id;

    auto it = std::remove_if(countries.begin(), countries.end(), [id](const Country& c) {
        return c.id == id;
        });

    if (it != countries.end()) {
        countries.erase(it, countries.end());
        std::cout << "Country removed.\n";
    }
    else {
        std::cout << "Country not found.\n";
    }
}

void CountryManager::update() {
    int id;
    std::cout << "Enter country ID to update: ";
    std::cin >> id;
    std::cin.ignore();

    for (auto& country : countries) {
        if (country.id == id) {
            std::cout << "Enter new country name: ";
            std::getline(std::cin, country.name);
            std::cout << "Country updated.\n";
            return;
        }
    }

    std::cout << "Country not found.\n";
}

void CountryManager::listAll() const {
    if (countries.empty()) {
        std::cout << "No countries found.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(30) << "Country Name"
        << "\n"
        << std::string(36, '-') << "\n";

    for (const auto& country : countries) {
        country.print();
    }
}


void CountryManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& country : countries) {
        out << country.id << ";" << country.name << "\n";
    }

    out.close();
    std::cout << "Countries saved to " << filename << "\n";
}

void CountryManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty country list.\n";
        return;
    }

    countries.clear();

    std::string line, token;
    int id;
    std::string name;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::getline(ss, token, ';'); id = std::stoi(token);
        std::getline(ss, name, ';');

        countries.emplace_back(id, name);
    }

    in.close();
    std::cout << "Countries loaded from " << filename << "\n";
}

Country* CountryManager::findById(int id) {
    for (auto& country : countries) {
        if (country.id == id) {
            return &country;
        }
    }
    return nullptr;
}
