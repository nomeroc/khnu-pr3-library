#include "Book.h"
#include <iostream>
#include <iomanip>

void Book::print() const {
    std::cout << std::left
        << std::setw(6) << id
        << std::setw(25) << title
        << std::setw(10) << genreId
        << std::setw(10) << authorId
        << std::setw(10) << countryId
        << std::setw(10) << std::fixed << std::setprecision(2) << price
        << "\n";
}