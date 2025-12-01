#include "MotorManager.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "Exceptions.h"

#include <fstream>
#include <iostream>
#include <limits>

void MotorManager::addMotor(std::unique_ptr<Engine> motor) {
    MotorRecord rec;
    rec.motor = std::move(motor);
    motors.push_back(std::move(rec));
}

void MotorManager::printAll() const {
    if (motors.empty()) {
        std::cout << "Список двигунів порожній.\n";
        return;
    }

    std::cout << "=== Список двигунів ===\n";
    std::size_t index = 1;

    for (const auto& rec : motors) {
        std::cout << index++ << ") ";
        rec.motor->print(std::cout);
        std::cout << '\n';
    }
}

void MotorManager::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw FileException("Не вдалося відкрити файл для запису: " + filename);
    }

    out << motors.size() << '\n';
    for (const auto& rec : motors) {
        rec.motor->saveToStream(out);
    }
}

void MotorManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw FileException("Не вдалося відкрити файл для читання: " + filename);
    }

    motors.clear();

    std::size_t count = 0;
    if (!(in >> count)) {
        throw FileException("Помилка читання кількості двигунів з файлу.");
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (std::size_t i = 0; i < count; ++i) {
        std::string type;
        std::getline(in, type);
        if (!in) {
            throw FileException("Помилка читання типу двигуна з файлу.");
        }

        std::unique_ptr<Engine> motor;

        if (type == "Servo") {
            motor = std::make_unique<ServoMotor>();
        } else if (type == "Stepper") {
            motor = std::make_unique<StepperMotor>();
        } else {
            throw FileException("Невідомий тип двигуна в файлі: " + type);
        }

        motor->loadFromStream(in);
        addMotor(std::move(motor));
    }
}

bool MotorManager::isEmpty() const {
    return motors.empty();
}
