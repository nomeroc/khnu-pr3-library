#include "AuthManager.h"
#include <iostream>

AuthManager::Role AuthManager::login() {
    int choice;

    std::cout << "========== Welcome ==========\n";
    std::cout << "1. Login as Admin\n";
    std::cout << "2. Login as User\n";
    std::cout << "Choose role: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string password;
        std::cout << "Enter admin password: ";
        std::cin >> password;

        if (password == "123") {  // Simple hardcoded password
            std::cout << "Access granted.\n";
            return Role::ADMIN;
        }
        else {
            std::cout << "Incorrect password. Defaulting to User mode.\n";
            return Role::USER;
        }
    }

    return Role::USER;
}
