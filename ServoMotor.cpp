#include "ServoMotor.h"
#include "Exceptions.h"

#include <iostream>
#include <limits>

ServoMotor::ServoMotor()
    : Engine(), angle(0) {}

ServoMotor::ServoMotor(const std::string& m, double p, double v, int a)
    : Engine(m, p, v), angle(a) {}

void ServoMotor::input() {
    Engine::input();

    while (true) {
        try {
            std::cout << "Введіть кут повороту (0–180 градусів): ";
            if (!(std::cin >> angle)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Кут повинен бути числом!");
            }

            if (angle < 0 || angle > 180) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Кут повинен бути в межах 0–180!");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } catch (const ValidationException& ex) {
            std::cerr << "Помилка: " << ex.what() << "\nСпробуйте ще раз.\n";
        }
    }
}

void ServoMotor::print(std::ostream& os) const {
    os << "[Серводвигун] ";
    Engine::print(os);
    os << ", Кут: " << angle << "°";
}

std::string ServoMotor::getType() const {
    return "Servo";
}

void ServoMotor::saveToStream(std::ostream& os) const {
    os << getType() << '\n';
    Engine::saveToStream(os);
    os << angle << '\n';
}

void ServoMotor::loadFromStream(std::istream& is) {
    Engine::loadFromStream(is);

    if (!(is >> angle)) {
        throw FileException("Помилка читання кута сервоприводу з файлу.");
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (angle < 0 || angle > 180) {
        throw FileException("У файлі некоректне значення кута сервоприводу (не 0–180).");
    }
}

ServoMotor ServoMotor::operator+(const ServoMotor& other) const {
    ServoMotor result(*this);

    result.model   = model + "+" + other.model;
    result.power   = power + other.power;
    result.voltage = (voltage + other.voltage) / 2.0;
    result.angle   = (angle + other.angle) / 2;

    return result;
}
