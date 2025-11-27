#pragma once
#include <string>
#include <iostream>

class Engine {
protected:
    std::string model;
    double power;
    double voltage;
public:
    Engine();
    Engine(const std::string& model, double power, double voltage);
    virtual ~Engine();
    virtual void input();
    virtual void print(std::ostream& os) const;
    virtual std::string getType() const = 0;
    virtual void saveToStream(std::ostream& os) const;
    virtual void loadFromStream(std::istream& is);
    bool operator<(const Engine& other) const;
};
