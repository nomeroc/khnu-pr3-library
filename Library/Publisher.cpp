#include "Publisher.h"
#include <iostream>
#include <iomanip>

void Publisher::print() const {
    std::cout << std::left
        << std::setw(6) << id
        << std::setw(20) << name
        << std::setw(20) << phone
        << std::setw(25) << email
        << std::setw(20) << chiefEditor
        << "\n";
}