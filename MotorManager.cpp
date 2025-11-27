#include "MotorManager.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <limits>

void MotorManager::addMotor(std::unique_ptr<Engine> m){
    motors.push_back({std::move(m)});
}

void MotorManager::printAll()const{
    if(motors.empty()){std::cout<<"Список порожній.
";return;}
    int i=1;for(const auto&m:motors){std::cout<<i++<<") ";m.motor->print(std::cout);std::cout<<"
";}
}

void MotorManager::saveToFile(const std::string&file)const{
    std::ofstream out(file);
    if(!out) throw FileException("Не вдалося відкрити файл.");
    out<<motors.size()<<"
";
    for(const auto&m:motors) m.motor->saveToStream(out);
}

void MotorManager::loadFromFile(const std::string&file){
    std::ifstream in(file);
    if(!in) throw FileException("Не вдалося відкрити файл.");
    motors.clear();
    size_t count; if(!(in>>count)) throw FileException("Помилка читання кількості.");
    in.ignore(1e6,'
');
    for(size_t i=0;i<count;i++){
        std::string type; std::getline(in,type);
        std::unique_ptr<Engine> m;
        if(type=="Servo") m=std::make_unique<ServoMotor>();
        else if(type=="Stepper") m=std::make_unique<StepperMotor>();
        else throw FileException("Невідомий тип: "+type);
        m->loadFromStream(in);
        addMotor(std::move(m));
    }
}
