#include "AdminInterface.h"
#include "AuthManager.h"
#include "AdminInterface.h"
#include "UserInterface.h"
#include "AuthManager.h"
#include <iostream>

int main() {
    AuthManager auth;
    AuthManager::Role role = auth.login();

    BookManager bookManager;
    AuthorManager authorManager;

    bookManager.loadFromFile("books.txt");
    authorManager.loadFromFile("authors.txt");

    if (role == AuthManager::Role::ADMIN) {
        AdminInterface admin;
        admin.run();
    }
    else {
        UserInterface user(bookManager, authorManager);
        user.run();
    }

    bookManager.saveToFile("books.txt");
    authorManager.saveToFile("authors.txt");

    return 0;
}