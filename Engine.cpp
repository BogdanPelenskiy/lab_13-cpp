#include "Engine.h"
#include "Exceptions.h"

#include <iostream>
#include <limits>

Engine::Engine()
    : model(""), power(0.0), voltage(0.0) {}

Engine::Engine(const std::string& m, double p, double v)
    : model(m), power(p), voltage(v) {}

Engine::~Engine() = default;

void Engine::input() {
    // Ввід моделі
    while (true) {
        try {
            std::cout << "Введіть модель двигуна: ";
            std::getline(std::cin, model);

            if (model.empty()) {
                throw ValidationException("Модель не може бути порожньою!");
            }

            break;
        } catch (const ValidationException& ex) {
            std::cerr << "Помилка: " << ex.what() << "\nСпробуйте ще раз.\n";
        }
    }

    // Ввід потужності
    while (true) {
        try {
            std::cout << "Введіть потужність (Вт): ";
            if (!(std::cin >> power)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Потужність повинна бути числом!");
            }

            if (power <= 0.0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Потужність повинна бути > 0!");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } catch (const ValidationException& ex) {
            std::cerr << "Помилка: " << ex.what() << "\nСпробуйте ще раз.\n";
        }
    }

    // Ввід напруги
    while (true) {
        try {
            std::cout << "Введіть напругу (В): ";
            if (!(std::cin >> voltage)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Напруга повинна бути числом!");
            }

            if (voltage <= 0.0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw ValidationException("Напруга повинна бути > 0!");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } catch (const ValidationException& ex) {
            std::cerr << "Помилка: " << ex.what() << "\nСпробуйте ще раз.\n";
        }
    }
}

void Engine::print(std::ostream& os) const {
    os << "Модель: " << model
       << ", Потужність: " << power << " Вт"
       << ", Напруга: " << voltage << " В";
}

void Engine::saveToStream(std::ostream& os) const {
    os << model << '\n'
       << power << '\n'
       << voltage << '\n';
}

void Engine::loadFromStream(std::istream& is) {
    std::getline(is, model);
    if (!is) {
        throw FileException("Помилка читання моделі двигуна з файлу.");
    }

    if (!(is >> power)) {
        throw FileException("Помилка читання потужності з файлу.");
    }

    if (!(is >> voltage)) {
        throw FileException("Помилка читання напруги з файлу.");
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (power <= 0.0 || voltage <= 0.0) {
        throw FileException("У файлі вказані некоректні значення потужності/напруги (<=0).");
    }
}

bool Engine::operator<(const Engine& other) const {
    return power < other.power;
}
