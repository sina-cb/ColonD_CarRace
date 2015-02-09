#include "SimpleDriver.h"

SimpleDriver::SimpleDriver(Car *car){
    this->car = car;

    if_drive = false;

    direction = 1;
    steer_value = this->car->SteeringAngle();
}

void SimpleDriver::drive(){

    if (if_drive){
        double* sensor_data = car->SensorData();

        car->EngineSpeed(-car->HorsePower());

        if (sensor_data[0] + sensor_data[1] > sensor_data[3] + sensor_data[4]){
            double current_angle = car->SteeringAngle();
            current_angle += b2_pi / 6;

            if (current_angle <= car->MaxSteeringAngle()){
                car->SteeringAngle(current_angle);
            }
        }else{
            double current_angle = car->SteeringAngle();
            current_angle -= b2_pi / 6;

            if (current_angle >= -car->MaxSteeringAngle()){
                car->SteeringAngle(current_angle);
            }
        }
    }

}

void SimpleDriver::Restart(){

}


