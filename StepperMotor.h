#pragma once

#include "Engine.h"

class StepperMotor : public Engine {
private:
    int stepsPerRev; // кроків на оберт

public:
    StepperMotor();
    StepperMotor(const std::string& model, double power, double voltage, int stepsPerRev);

    void input() override;
    void print(std::ostream& os) const override;
    std::string getType() const override;

    void saveToStream(std::ostream& os) const override;
    void loadFromStream(std::istream& is) override;
};
