#include "AdminInterface.h"
#include "UserInterface.h"
#include "AuthManager.h"

#include <iostream>
#include <windows.h>
#include "ConsoleUtils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    BookManager bookManager;
    AuthorManager authorManager;

    bookManager.loadFromFile("books.json");
    authorManager.loadFromFile("authors.json");

    int mode;
    do {
        clearScreen();
        std::cout << "\nSelect mode:\n";
        std::cout << "1. Admin\n";
        std::cout << "2. User\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> mode;

        if (mode == 1) {
            AuthManager auth;
            AuthManager::Role role = auth.login();
            if (role == AuthManager::Role::ADMIN) {
                AdminInterface admin(bookManager, authorManager /*, other managers */);
                admin.run();
            }
            else {
                std::cout << "Incorrect password. Access denied.\n";
            }
        }
        else if (mode == 2) {
            UserInterface user(bookManager, authorManager);
            user.run();
        }
        else if (mode == 0) {
            std::cout << "Goodbye!\n";
        }
        else {
            std::cout << "Invalid option.\n";
        }

    } while (mode != 0);

    return 0;
}
