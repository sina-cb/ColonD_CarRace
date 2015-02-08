#include "SimpleDriver.h"

SimpleDriver::SimpleDriver(Car *car){
    this->car = car;

    direction = 1;
    steer_value = this->car->SteeringAngle();
}

void SimpleDriver::drive(){

//    if (direction > 0){
//        if (steer_value < car->MaxSteeringAngle()){
//            steer_value += car->MaxSteeringAngle() / 10.0;
//            car->SteeringAngle(steer_value);
//        }else{
//            direction = -1;
//        }
//    }else if (direction < 0){
//        if (steer_value > -car->MaxSteeringAngle()){
//            steer_value -= car->MaxSteeringAngle() / 10.0;
//            car->SteeringAngle(steer_value);
//        }else{
//            direction = 1;
//        }
//    }

}


