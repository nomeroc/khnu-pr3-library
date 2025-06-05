#include "ReleaseManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>

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

    saveToFile("releases.json");
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

    saveToFile("releases.json");
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

    saveToFile("releases.json");
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

void ReleaseManager::countCopiesByPublisherInYear(const PublisherManager& publisherManager, const std::string& year) const {
    std::map<int, int> publisherCopyCount;

    for (const auto& release : releases) {
        if (release.releaseDate.substr(0, 4) == year) {
            publisherCopyCount[release.publisherId] += release.copies;
        }
    }

    std::cout << "\nBook copies released in " << year << " by publisher:\n";
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(30) << "Publisher"
        << std::setw(10) << "Copies"
        << "\n"
        << std::string(46, '-') << "\n";

    for (const auto& publisher : publisherManager.getAll()) {
        int count = publisherCopyCount[publisher.id];
        if (count > 0) {
            std::cout << std::left
                << std::setw(6) << publisher.id
                << std::setw(30) << publisher.name
                << std::setw(10) << count
                << "\n";
        }
    }
}

void ReleaseManager::showBookWithMaxCopiesInYear(const BookManager& bookManager, const std::string& year) const {
    int maxCopies = -1;
    int maxBookId = -1;

    for (const auto& release : releases) {
        if (release.releaseDate.find(year) != std::string::npos) {
            if (release.copies > maxCopies) {
                maxCopies = release.copies;
                maxBookId = release.bookId;
            }
        }
    }

    if (maxBookId != -1) {
        const auto& books = bookManager.getAll();
        auto it = std::find_if(books.begin(), books.end(), [=](const Book& b) {
            return b.id == maxBookId;
            });

        if (it != books.end()) {
            std::cout << "\nBook with most copies in " << year << ":\n";
            std::cout << "Title: " << it->title << "\n";
            std::cout << "Copies: " << maxCopies << "\n";
        }
        else {
            std::cout << "\nBook data not found for ID " << maxBookId << "\n";
        }
    }
    else {
        std::cout << "\nNo releases found for year " << year << ".\n";
    }
}

void ReleaseManager::countBooksPerPublisher(const PublisherManager& publisherManager) const {
    std::map<int, std::set<int>> publisherBooks;

    // Build map: publisherId → set of unique bookIds
    for (const auto& release : releases) {
        publisherBooks[release.publisherId].insert(release.bookId);
    }

    std::cout << "\nBooks Released by Each Publisher:\n";
    std::cout << std::left << std::setw(6) << "ID"
        << std::setw(25) << "Publisher Name"
        << std::setw(15) << "Book Count"
        << "\n" << std::string(46, '-') << "\n";

    for (const auto& entry : publisherBooks) {
        int publisherId = entry.first;
        const auto& booksSet = entry.second;

        const Publisher* pub = publisherManager.findById(publisherId);
        std::string name = pub ? pub->name : "Unknown";

        std::cout << std::setw(6) << publisherId
            << std::setw(25) << name
            << std::setw(15) << booksSet.size()
            << "\n";
    }

}

void ReleaseManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    json j = releases;
    out << j.dump(4);
    out.close();

    std::cout << "Releases saved to " << filename << "\n";
}


void ReleaseManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File not found. Starting with empty release list.\n";
        return;
    }

    json j;
    in >> j;
    releases = j.get<std::vector<Release>>();
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