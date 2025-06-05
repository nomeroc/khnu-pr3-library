#include "AuthManager.h"
#include "ConsoleUtils.h"
#include <iostream>

AuthManager::Role AuthManager::login() {
    std::string inputPassword;

    std::cout << "Enter password: ";
    inputPassword = getMaskedInput();

    if (inputPassword == "123") {
        std::cout << "Logged in as ADMIN.\n";
        pause();
        return Role::ADMIN;
    }
    else {
        std::cout << "Access denied.\n";
        pause();
        return Role::UNKNOWN;
    }
}
