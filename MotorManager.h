#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Engine.h"

class MotorManager {
public:
    struct MotorRecord {
        std::unique_ptr<Engine> motor;
    };

private:
    std::vector<MotorRecord> motors;

public:
    MotorManager() = default;
    ~MotorManager() = default;

    void addMotor(std::unique_ptr<Engine> motor);
    void printAll() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    bool isEmpty() const;
};
