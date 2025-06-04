#pragma once
#include <string>
#include "json.hpp"  // Adjust path if needed

using json = nlohmann::json;

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

// ✅ JSON serialization
inline void to_json(json& j, const Publisher& p) {
    j = json{
        {"id", p.id},
        {"name", p.name},
        {"address", p.address},
        {"phone", p.phone},
        {"email", p.email},
        {"chiefEditor", p.chiefEditor}
    };
}

inline void from_json(const json& j, Publisher& p) {
    j.at("id").get_to(p.id);
    j.at("name").get_to(p.name);
    j.at("address").get_to(p.address);
    j.at("phone").get_to(p.phone);
    j.at("email").get_to(p.email);
    j.at("chiefEditor").get_to(p.chiefEditor);
}
