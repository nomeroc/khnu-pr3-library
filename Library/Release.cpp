#include "Release.h"
#include <iostream>
#include <iomanip>

void Release::print() const {
    std::cout << std::left
        << std::setw(10) << batchId
        << std::setw(10) << bookId
        << std::setw(15) << publisherId
        << std::setw(10) << copies
        << std::setw(15) << releaseDate
        << "\n";
}