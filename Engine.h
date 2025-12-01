#pragma once

#include <string>
#include <iostream>

class Engine {
protected:
    std::string model;
    double power;   // Вт
    double voltage; // В

public:
    Engine();
    Engine(const std::string& model, double power, double voltage);
    virtual ~Engine();

    // Ввід з клавіатури з перевірками
    virtual void input();

    // Поліморфний вивід
    virtual void print(std::ostream& os) const;

    // Тип двигуна (Servo / Stepper)
    virtual std::string getType() const = 0;

    // Файловий ввід/вивід
    virtual void saveToStream(std::ostream& os) const;
    virtual void loadFromStream(std::istream& is);

    // Порівняння за потужністю
    bool operator<(const Engine& other) const;
};
