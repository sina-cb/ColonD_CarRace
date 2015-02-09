#include "ANNDriver.h"

ANNDriver::ANNDriver(Car *car){
    this->car = car;
    if_drive = false;
}

void ANNDriver::drive(){

    double* sensor_data = car->SensorData();

    if (if_drive){

        car->EngineSpeed(-car->HorsePower());
    }

    cout << "Sensor data: ";
    for (int i = 0; i < car->SENSOR_COUNT; i++){
        cout << sensor_data[i] << "\t";
    }

    cout << "True value";

    cout << endl;

}

void ANNDriver::Restart(){

}


