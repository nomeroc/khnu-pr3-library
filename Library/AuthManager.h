#pragma once
#include <string>

class AuthManager {
public:
    enum class Role { ADMIN, USER };

    Role login();  // prompt user for role and return it
};
