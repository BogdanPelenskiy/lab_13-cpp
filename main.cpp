#include <iostream>
#include <memory>
#include <locale>
#include <limits>

#include "MotorManager.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "Exceptions.h"

int main() {
    std::setlocale(LC_ALL, "uk_UA.UTF-8");

    MotorManager manager;
    const std::string filename = "motors.txt";

    while (true) {
        std::cout << "\n=== МЕНЮ ===\n"
                  << "1. Додати серводвигун\n"
                  << "2. Додати кроковий двигун\n"
                  << "3. Показати всі двигуни\n"
                  << "4. Зберегти у файл\n"
                  << "5. Завантажити з файлу\n"
                  << "6. Демонстрація оператора + (ServoMotor)\n"
                  << "0. Вихід\n"
                  << "Ваш вибір: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некоректне значення, спробуйте ще.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            if (choice == 1) {
                auto motor = std::make_unique<ServoMotor>();
                motor->input();
                manager.addMotor(std::move(motor));
            } else if (choice == 2) {
                auto motor = std::make_unique<StepperMotor>();
                motor->input();
                manager.addMotor(std::move(motor));
            } else if (choice == 3) {
                manager.printAll();
            } else if (choice == 4) {
                manager.saveToFile(filename);
                std::cout << "Дані збережено у файл: " << filename << "\n";
            } else if (choice == 5) {
                manager.loadFromFile(filename);
                std::cout << "Дані завантажено з файлу: " << filename << "\n";
            } else if (choice == 6) {
                std::cout << "Демонстрація оператора + для двох серводвигунів:\n";

                ServoMotor s1("SG90", 4.8, 5.0, 120);
                ServoMotor s2("MG996R", 10.0, 6.0, 90);
                ServoMotor s3 = s1 + s2;

                std::cout << "s1: ";
                s1.print(std::cout);
                std::cout << "\n";

                std::cout << "s2: ";
                s2.print(std::cout);
                std::cout << "\n";

                std::cout << "s1 + s2: ";
                s3.print(std::cout);
                std::cout << "\n";
            } else if (choice == 0) {
                std::cout << "Вихід з програми.\n";
                break;
            } else {
                std::cout << "Невірний пункт меню.\n";
            }
        } catch (const ValidationException& ex) {
            std::cerr << "Помилка введення: " << ex.what() << "\n";
        } catch (const FileException& ex) {
            std::cerr << "Помилка файлу: " << ex.what() << "\n";
        } catch (const std::exception& ex) {
            std::cerr << "Стандартний виняток: " << ex.what() << "\n";
        } catch (...) {
            std::cerr << "Невідомий виняток!\n";
        }
    }

    return 0;
}
