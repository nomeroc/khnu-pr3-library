#include "AdminInterface.h"
#include "AuthManager.h"
#include "AdminInterface.h"
#include "UserInterface.h"
#include "AuthManager.h"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    AuthManager auth;
    AuthManager::Role role = auth.login();

    BookManager bookManager;
    AuthorManager authorManager;

    bookManager.loadFromFile("books.json");
    authorManager.loadFromFile("authors.json");

    if (role == AuthManager::Role::ADMIN) {
        AdminInterface admin;
        admin.run();
    }
    else {
        UserInterface user(bookManager, authorManager);
        user.run();
    }

    return 0;
}