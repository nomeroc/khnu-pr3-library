#include "UserInterface.h"
#include <iostream>
#include <limits>
#include "ConsoleUtils.h"

UserInterface::UserInterface(BookManager& bookMgr, AuthorManager& authorMgr)
    : bookManager(bookMgr), authorManager(authorMgr) {
}

void UserInterface::showBooks() {
    clearScreen();
    std::cout << "\nAll Books:\n";
    bookManager.listAll();
    pause();
}

void UserInterface::showAuthors() {
    clearScreen();
    std::cout << "\nAll Authors:\n";
    authorManager.listAll();
    pause();
}

void UserInterface::searchBooksByAuthor() {
    clearScreen();
    int authorId;
    std::cout << "Enter author ID: ";
    std::cin >> authorId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const Author* author = authorManager.findById(authorId);
    if (!author) {
        std::cout << "Author not found.\n";
    }
    else {
        std::cout << "\nBooks by " << author->lastName << " " << author->firstName << ":\n";
        bool found = false;
        for (const auto& book : bookManager.getAll()) {
            if (book.authorId == authorId) {
                book.print();
                found = true;
            }
        }
        if (!found) std::cout << "No books found for this author.\n";
    }
    pause();
}

void UserInterface::filterBooksByPrice() {
    clearScreen();
    float min, max;
    std::cout << "Enter min price: ";
    std::cin >> min;
    std::cout << "Enter max price: ";
    std::cin >> max;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nBooks priced between " << min << " and " << max << ":\n";
    bool found = false;
    for (const auto& book : bookManager.getAll()) {
        if (book.price >= min && book.price <= max) {
            book.print();
            found = true;
        }
    }
    if (!found) std::cout << "No books found in this price range.\n";
    pause();
}

void UserInterface::run() {
    int choice;
    do {
        clearScreen();
        std::cout << "\n========== User Menu ==========\n";
        std::cout << "1. Show all books\n";
        std::cout << "2. Show all authors\n";
        std::cout << "3. Search books by author ID\n";
        std::cout << "4. Filter books by price range\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose option: ";
        std::cin >> choice;

        switch (choice) {
        case 1: showBooks(); break;
        case 2: showAuthors(); break;
        case 3: searchBooksByAuthor(); break;
        case 4: filterBooksByPrice(); break;
        case 0: std::cout << "Goodbye!\n"; break;
        default: std::cout << "Invalid option.\n"; pause();
        }

    } while (choice != 0);
}
