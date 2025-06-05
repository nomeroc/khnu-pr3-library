#include "PublisherManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;

void PublisherManager::add() {
    int id;
    std::string name, address, phone, email, chiefEditor;

    std::cout << "Enter publisher ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter address: ";
    std::getline(std::cin, address);

    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);

    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    std::cout << "Enter chief editor: ";
    std::getline(std::cin, chiefEditor);

    publishers.emplace_back(id, name, address, phone, email, chiefEditor);
    std::cout << "Publisher added successfully.\n";

    saveToFile("publishers.json");
}

void PublisherManager::remove() {
    int id;
    std::cout << "Enter publisher ID to remove: ";
    std::cin >> id;

    auto it = std::remove_if(publishers.begin(), publishers.end(), [id](const Publisher& p) {
        return p.id == id;
        });

    if (it != publishers.end()) {
        publishers.erase(it, publishers.end());
        std::cout << "Publisher removed.\n";
    }
    else {
        std::cout << "Publisher not found.\n";
    }

    saveToFile("publishers.json");
}

void PublisherManager::update() {
    int id;
    std::cout << "Enter publisher ID to update: ";
    std::cin >> id;
    std::cin.ignore();

    for (auto& publisher : publishers) {
        if (publisher.id == id) {
            std::cout << "Enter new name: ";
            std::getline(std::cin, publisher.name);

            std::cout << "Enter new address: ";
            std::getline(std::cin, publisher.address);

            std::cout << "Enter new phone: ";
            std::getline(std::cin, publisher.phone);

            std::cout << "Enter new email: ";
            std::getline(std::cin, publisher.email);

            std::cout << "Enter new chief editor: ";
            std::getline(std::cin, publisher.chiefEditor);

            std::cout << "Publisher updated.\n";
            return;
        }
    }

    std::cout << "Publisher not found.\n";

    saveToFile("publishers.json");
}

void PublisherManager::listAll() const {
    if (publishers.empty()) {
        std::cout << "No publishers found.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(20) << "Name"
        << std::setw(20) << "Phone"
        << std::setw(25) << "Email"
        << std::setw(20) << "Editor"
        << "\n"
        << std::string(91, '-') << "\n";

    for (const auto& publisher : publishers) {
        publisher.print();
    }
}

void PublisherManager::listPublishersWithoutEmail() const {
    std::cout << "\nPublishers without email:\n";

    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(20) << "Name"
        << std::setw(20) << "Phone"
        << std::setw(25) << "Email"
        << std::setw(20) << "Editor"
        << "\n"
        << std::string(91, '-') << "\n";

    bool found = false;
    for (const auto& publisher : publishers) {
        if (publisher.email.empty() || publisher.email == "-") {
            publisher.print();
            found = true;
        }
    }

    if (!found)
        std::cout << "All publishers have an email.\n";
}

void PublisherManager::countPublishers() const {
    std::cout << "\nTotal number of publishers: " << publishers.size() << "\n";
}

void PublisherManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    json j = publishers;
    out << j.dump(4);
    out.close();

    std::cout << "Publishers saved to " << filename << "\n";
}


void PublisherManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty publisher list.\n";
        return;
    }

    json j;
    in >> j;
    publishers = j.get<std::vector<Publisher>>();
    in.close();

    std::cout << "Publishers loaded from " << filename << "\n";
}


Publisher* PublisherManager::findById(int id) {
    for (auto& publisher : publishers) {
        if (publisher.id == id) {
            return &publisher;
        }
    }
    return nullptr;
}

const std::vector<Publisher>& PublisherManager::getAll() const {
    return publishers;
}

const Publisher* PublisherManager::findById(int id) const {
    for (const auto& pub : publishers) {
        if (pub.id == id) return &pub;
    }
    return nullptr;
}
