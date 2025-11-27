#include "Engine.h"
#include "Exceptions.h"
#include <limits>
#include <iostream>

Engine::Engine():model(""),power(0),voltage(0){}
Engine::Engine(const std::string&m,double p,double v):model(m),power(p),voltage(v){}
Engine::~Engine()=default;

void Engine::input(){
    while(true){
        try{
            std::cout<<"Введіть модель двигуна: ";
            std::getline(std::cin,model);
            if(model.empty()) throw ValidationException("Модель не може бути порожньою!");
            break;
        }catch(const ValidationException&ex){std::cerr<<"Помилка: "<<ex.what()<<"
";}}
    while(true){
        try{
            std::cout<<"Введіть потужність (Вт): ";
            if(!(std::cin>>power)){std::cin.clear();std::cin.ignore(1e6,'
');throw ValidationException("Потужність повинна бути числом!");}
            if(power<=0){std::cin.ignore(1e6,'
');throw ValidationException("Потужність повинна бути >0!");}
            std::cin.ignore(1e6,'
');break;
        }catch(const ValidationException&ex){std::cerr<<"Помилка: "<<ex.what()<<"
";}}
    while(true){
        try{
            std::cout<<"Введіть напругу (В): ";
            if(!(std::cin>>voltage)){std::cin.clear();std::cin.ignore(1e6,'
');throw ValidationException("Напруга повинна бути числом!");}
            if(voltage<=0){std::cin.ignore(1e6,'
');throw ValidationException("Напруга повинна бути >0!");}
            std::cin.ignore(1e6,'
');break;
        }catch(const ValidationException&ex){std::cerr<<"Помилка: "<<ex.what()<<"
";}}
}

void Engine::print(std::ostream&os)const{
    os<<"Модель: "<<model<<", Потужність: "<<power<<" Вт, Напруга: "<<voltage<<" В";
}

void Engine::saveToStream(std::ostream&os)const{
    os<<model<<"
"<<power<<"
"<<voltage<<"
";
}

void Engine::loadFromStream(std::istream&is){
    std::getline(is,model);
    if(!is) throw FileException("Помилка читання моделі.");
    if(!(is>>power)) throw FileException("Помилка читання потужності.");
    if(!(is>>voltage)) throw FileException("Помилка читання напруги.");
    is.ignore(1e6,'
');
    if(power<=0||voltage<=0) throw FileException("Невірні значення у файлі.");
}

bool Engine::operator<(const Engine&o)const{return power<o.power;}
