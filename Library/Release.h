#pragma once
#include <string>

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
