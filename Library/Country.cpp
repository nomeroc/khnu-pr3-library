#include "Country.h"
#include <iostream>
#include <iomanip>

void Country::print() const {
    std::cout << std::left
        << std::setw(6) << id
        << std::setw(30) << name
        << "\n";
}