#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Release {
public:
    int batchId;
    int bookId;
    int publisherId;
    int copies;
    std::string releaseDate;

    Release() = default;
    Release(int batchId, int bookId, int publisherId, int copies, const std::string& releaseDate)
        : batchId(batchId), bookId(bookId), publisherId(publisherId), copies(copies), releaseDate(releaseDate) {
    }

    void print() const;
};

inline void to_json(json& j, const Release& r) {
    j = json{
        {"batchId", r.batchId},
        {"bookId", r.bookId},
        {"publisherId", r.publisherId},
        {"copies", r.copies},
        {"releaseDate", r.releaseDate}
    };
}

inline void from_json(const json& j, Release& r) {
    j.at("batchId").get_to(r.batchId);
    j.at("bookId").get_to(r.bookId);
    j.at("publisherId").get_to(r.publisherId);
    j.at("copies").get_to(r.copies);
    j.at("releaseDate").get_to(r.releaseDate);
}
