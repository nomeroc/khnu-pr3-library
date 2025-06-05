#pragma once
#include <string>

class AuthManager {
public:
    enum class Role { ADMIN, USER, UNKNOWN };

    Role login();  // Determines role based on password
};
