#include "ServoMotor.h"
#include "Exceptions.h"
#include <limits>
#include <iostream>

ServoMotor::ServoMotor():Engine(),angle(0){}
ServoMotor::ServoMotor(const std::string&m,double p,double v,int a):Engine(m,p,v),angle(a){}

void ServoMotor::input(){
    Engine::input();
    while(true){
        try{
            std::cout<<"Введіть кут (0–180): ";
            if(!(std::cin>>angle)){std::cin.clear();std::cin.ignore(1e6,'
');throw ValidationException("Кут повинен бути числом!");}
            if(angle<0||angle>180){std::cin.ignore(1e6,'
');throw ValidationException("Кут 0–180!");}
            std::cin.ignore(1e6,'
');break;
        }catch(const ValidationException&ex){std::cerr<<"Помилка: "<<ex.what()<<"
";}}
}

void ServoMotor::print(std::ostream&os)const{
    os<<"[Серводвигун] ";Engine::print(os);os<<", Кут: "<<angle<<"°";
}

void ServoMotor::saveToStream(std::ostream&os)const{
    os<<"Servo
";Engine::saveToStream(os);os<<angle<<"
";
}

void ServoMotor::loadFromStream(std::istream&is){
    Engine::loadFromStream(is);
    if(!(is>>angle)) throw FileException("Помилка читання кута.");
    is.ignore(1e6,'
');
    if(angle<0||angle>180) throw FileException("Кут поза межами 0–180.");
}

ServoMotor ServoMotor::operator+(const ServoMotor&o)const{
    ServoMotor r=*this;
    r.model=model+"+"+o.model;
    r.power=power+o.power;
    r.voltage=(voltage+o.voltage)/2;
    r.angle=(angle+o.angle)/2;
    return r;
}
