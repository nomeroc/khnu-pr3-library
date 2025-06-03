#pragma once
#include "BookManager.h"
#include "AuthorManager.h"

class UserInterface {
private:
    BookManager& bookManager;
    AuthorManager& authorManager;

    void showBooks();
    void showAuthors();
    void searchBooksByAuthor();
    void filterBooksByPrice();

public:
    UserInterface(BookManager& bookMgr, AuthorManager& authorMgr);
    void run();
};
