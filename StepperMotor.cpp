#include "StepperMotor.h"
#include "Exceptions.h"
#include <limits>
#include <iostream>

StepperMotor::StepperMotor():Engine(),stepsPerRev(0){}
StepperMotor::StepperMotor(const std::string&m,double p,double v,int s):Engine(m,p,v),stepsPerRev(s){}

void StepperMotor::input(){
    Engine::input();
    while(true){
        try{
            std::cout<<"Введіть кроки (>0): ";
            if(!(std::cin>>stepsPerRev)){std::cin.clear();std::cin.ignore(1e6,'
');throw ValidationException("Кроки — число!");}
            if(stepsPerRev<=0){std::cin.ignore(1e6,'
');throw ValidationException("Кроки >0!");}
            std::cin.ignore(1e6,'
');break;
        }catch(const ValidationException&ex){std::cerr<<"Помилка: "<<ex.what()<<"
";}}
}

void StepperMotor::print(std::ostream&os)const{
    os<<"[Кроковий двигун] ";Engine::print(os);os<<", Кроків/оберт: "<<stepsPerRev;
}

void StepperMotor::saveToStream(std::ostream&os)const{
    os<<"Stepper
";Engine::saveToStream(os);os<<stepsPerRev<<"
";
}

void StepperMotor::loadFromStream(std::istream&is){
    Engine::loadFromStream(is);
    if(!(is>>stepsPerRev)) throw FileException("Помилка читання кроків.");
    is.ignore(1e6,'
');
    if(stepsPerRev<=0) throw FileException("Кроки <=0.");
}
