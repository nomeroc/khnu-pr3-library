#pragma once
#include <vector>
#include "Genre.h"
#include "IDatabaseEntity.h"

class GenreManager : public IDatabaseEntity {
private:
    std::vector<Genre> genres;

public:
    void add() override;
    void remove() override;
    void update() override;
    void listAll() const override;

    Genre* findById(int id);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void deleteGenreByName(const std::string& name);

    const std::vector<Genre>& getAll() const;
};
