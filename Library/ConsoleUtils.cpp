// ConsoleUtils.cpp
#include "ConsoleUtils.h"
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

std::string getMaskedInput() {
    std::string password;
    char ch;

#ifdef _WIN32
    while ((ch = _getch()) != '\r') { // Enter key
        if (ch == '\b') { // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
#else
    struct termios oldt {}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO); // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n') {
        if (ch == 127 || ch == '\b') { // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    std::cout << '\n';
    return password;
}
