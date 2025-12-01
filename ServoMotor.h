#pragma once

#include "Engine.h"

class ServoMotor : public Engine {
private:
    int angle; // 0–180

public:
    ServoMotor();
    ServoMotor(const std::string& model, double power, double voltage, int angle);

    void input() override;
    void print(std::ostream& os) const override;
    std::string getType() const override;

    void saveToStream(std::ostream& os) const override;
    void loadFromStream(std::istream& is) override;

    // Перевантаження оператора +
    ServoMotor operator+(const ServoMotor& other) const;
};
