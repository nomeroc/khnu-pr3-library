#include "Genre.h"
#include <iostream>
#include <iomanip>

void Genre::print() const {
    std::cout << std::left
        << std::setw(6) << id
        << std::setw(30) << name
        << "\n";
}