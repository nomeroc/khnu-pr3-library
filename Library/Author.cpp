#include "Author.h"
#include <iostream>
#include <iomanip>

void Author::print() const {
    std::cout << std::left
        << std::setw(6) << id
        << std::setw(15) << lastName
        << std::setw(15) << firstName
        << std::setw(15) << middleName
        << std::setw(10) << countryId
        << "\n";
}