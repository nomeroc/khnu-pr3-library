#include "ConsoleUtils.h"
#include <iostream>
#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
