#include "AdminInterface.h"
#include <iostream>
#include <cstdlib>
#include "ConsoleUtils.h"

AdminInterface::AdminInterface() {
    bookManager.loadFromFile("books.txt");
    authorManager.loadFromFile("authors.txt");
    genreManager.loadFromFile("genres.txt");
    countryManager.loadFromFile("countries.txt");
    publisherManager.loadFromFile("publishers.txt");
    releaseManager.loadFromFile("releases.txt");
}

void AdminInterface::showEntityMenu(const std::string& entityName, IDatabaseEntity& manager) {
    int choice;
    do {
        clearScreen();
        std::cout << "\n=== " << entityName << " Menu ===\n";
        std::cout << "1. Add\n";
        std::cout << "2. Remove\n";
        std::cout << "3. Update\n";
        std::cout << "4. List All\n";
        std::cout << "0. Back\n";
        std::cout << "Choose option: ";
        std::cin >> choice;

        switch (choice) {
        case 1: manager.add(); break;
        case 2: manager.remove(); break;
        case 3: manager.update(); break;
        case 4: manager.listAll(); break;
        case 0: break;
        default: std::cout << "Invalid option.\n";
        }
        if (choice != 0) pause();
    } while (choice != 0);
}

void AdminInterface::run() {
    int choice;
    do {
        clearScreen();
        std::cout << "\n======= Admin Panel =======\n";
        std::cout << "1. Manage Books\n";
        std::cout << "2. Manage Authors\n";
        std::cout << "3. Manage Genres\n";
        std::cout << "4. Manage Countries\n";
        std::cout << "5. Manage Publishers\n";
        std::cout << "6. Manage Releases\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose section: ";
        std::cin >> choice;

        switch (choice) {
        case 1: showEntityMenu("Books", bookManager); break;
        case 2: showEntityMenu("Authors", authorManager); break;
        case 3: showEntityMenu("Genres", genreManager); break;
        case 4: showEntityMenu("Countries", countryManager); break;
        case 5: showEntityMenu("Publishers", publisherManager); break;
        case 6: showEntityMenu("Releases", releaseManager); break;
        case 0:
            bookManager.saveToFile("books.txt");
            authorManager.saveToFile("authors.txt");
            genreManager.saveToFile("genres.txt");
            countryManager.saveToFile("countries.txt");
            publisherManager.saveToFile("publishers.txt");
            releaseManager.saveToFile("releases.txt");
            std::cout << "Exiting...\n";
            break;

        default: std::cout << "Invalid option.\n";
        }
    } while (choice != 0);
}
