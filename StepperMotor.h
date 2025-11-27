#pragma once
#include "Engine.h"

class StepperMotor:public Engine{
    int stepsPerRev;
public:
    StepperMotor();
    StepperMotor(const std::string&model,double power,double voltage,int steps);
    void input()override;
    void print(std::ostream&os)const override;
    std::string getType()const override{return "Stepper";}
    void saveToStream(std::ostream&os)const override;
    void loadFromStream(std::istream&is)override;
};
