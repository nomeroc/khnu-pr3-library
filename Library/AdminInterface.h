#pragma once

#include "BookManager.h"
#include "AuthorManager.h"
#include "GenreManager.h"
#include "CountryManager.h"
#include "PublisherManager.h"
#include "ReleaseManager.h"

class AdminInterface {
private:
    BookManager& bookManager;
    AuthorManager& authorManager;
    GenreManager genreManager;
    CountryManager countryManager;
    PublisherManager publisherManager;
    ReleaseManager releaseManager;

    void showEntityMenu(const std::string& entityName, IDatabaseEntity& manager);

public:
    AdminInterface(BookManager& bookMgr, AuthorManager& authorMgr);
    void run();  // entry point
};
