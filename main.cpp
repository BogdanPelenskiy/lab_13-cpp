#include <iostream>
#include <memory>
#include <locale>
#include "MotorManager.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "Exceptions.h"

int main(){
    std::setlocale(LC_ALL,"uk_UA.UTF-8");
    MotorManager manager;
    const std::string file="motors.txt";
    while(true){
        std::cout<<"\n=== МЕНЮ ===\n1.Додати Servo\n2.Додати Stepper\n3.Показати\n4.Зберегти\n5.Завантажити\n6.Оператор +\n0.Вихід\nВаш вибір: ";
        int c; if(!(std::cin>>c)){std::cin.clear();std::cin.ignore(1e6,'
');continue;} std::cin.ignore(1e6,'
');
        try{
            if(c==1){auto m=std::make_unique<ServoMotor>();m->input();manager.addMotor(std::move(m));}
            else if(c==2){auto m=std::make_unique<StepperMotor>();m->input();manager.addMotor(std::move(m));}
            else if(c==3){manager.printAll();}
            else if(c==4){manager.saveToFile(file);std::cout<<"Збережено.\n";}
            else if(c==5){manager.loadFromFile(file);std::cout<<"Завантажено.\n";}
            else if(c==6){
                ServoMotor a("SG90",4.8,5,120),b("MG996",10,6,90);
                ServoMotor c=a+b;
                std::cout<<"Результат: "; c.print(std::cout); std::cout<<"\n";
            }
            else if(c==0) break;
        }catch(const std::exception&ex){std::cerr<<"Помилка: "<<ex.what()<<"\n";}
    }
}
