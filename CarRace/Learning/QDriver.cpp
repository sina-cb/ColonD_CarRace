#include "QDriver.h"

QDriver::QDriver(Car *car){
    this->car = car;

    direction = 1;
    steer_value = this->car->SteeringAngle();
}

void QDriver::drive(){



}

void QDriver::Restart(){

}


