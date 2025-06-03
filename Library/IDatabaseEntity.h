#pragma once

class IDatabaseEntity {
public:
    virtual void add() = 0;
    virtual void remove() = 0;
    virtual void update() = 0;
    virtual void listAll() const = 0;
    virtual ~IDatabaseEntity() {}
};
