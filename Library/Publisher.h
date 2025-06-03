#pragma once
#include <string>

class Publisher {
public:
    int id;
    std::string name;
    std::string address;
    std::string phone;
    std::string email;
    std::string chiefEditor;

    Publisher() = default;

    Publisher(int id, const std::string& name, const std::string& address,
        const std::string& phone, const std::string& email, const std::string& chiefEditor)
        : id(id), name(name), address(address), phone(phone), email(email), chiefEditor(chiefEditor) {
    }

    void print() const;
};
