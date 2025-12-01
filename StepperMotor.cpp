#include "StepperMotor.h"
#include "Exceptions.h"

#include <iostream>
#include <limits>

StepperMotor::StepperMotor()
    : Engine(), stepsPerRev(0) {}

StepperMotor::StepperMotor(const std::string& m, double p, double v, int steps)
    : Engine(m, p, v), stepsPerRev(steps) {}

void StepperMotor::input() {
    Engine::input();

    while (true) {
        try {
            std::cout << "Введіть кількість кроків на оберт (>0): ";
            if (!(std::cin >> stepsPerRev)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Кількість кроків повинна бути числом!");
            }

            if (stepsPerRev <= 0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Кількість кроків повинна бути > 0!");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } catch (const ValidationException& ex) {
            std::cerr << "Помилка: " << ex.what() << "\nСпробуйте ще раз.\n";
        }
    }
}

void StepperMotor::print(std::ostream& os) const {
    os << "[Кроковий двигун] ";
    Engine::print(os);
    os << ", Кроків/оберт: " << stepsPerRev;
}

std::string StepperMotor::getType() const {
    return "Stepper";
}

void StepperMotor::saveToStream(std::ostream& os) const {
    os << getType() << '\n';
    Engine::saveToStream(os);
    os << stepsPerRev << '\n';
}

void StepperMotor::loadFromStream(std::istream& is) {
    Engine::loadFromStream(is);

    if (!(is >> stepsPerRev)) {
        throw FileException("Помилка читання кроків крокового двигуна з файлу.");
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (stepsPerRev <= 0) {
        throw FileException("У файлі некоректна кількість кроків (<=0).");
    }
}
