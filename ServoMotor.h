#pragma once
#include "Engine.h"

class ServoMotor:public Engine{
    int angle;
public:
    ServoMotor();
    ServoMotor(const std::string&model,double power,double voltage,int angle);
    void input()override;
    void print(std::ostream&os)const override;
    std::string getType()const override{return "Servo";}
    void saveToStream(std::ostream&os)const override;
    void loadFromStream(std::istream&is)override;
    ServoMotor operator+(const ServoMotor&other)const;
};
