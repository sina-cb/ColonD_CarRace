#ifndef DRIVER_H
#define DRIVER_H

#include "../Game/Car.h"

class Driver{

public:
    Driver(){
        if_drive = false;
    }
    Driver(Car* car);

    virtual ~Driver(){
        delete car;
    }

    void start(){
        car->EngineSpeed(-car->HorsePower());
        car->SteeringAngle(0);
        if_drive = true;
    }

    void stop(){
        car->EngineSpeed(0);
        car->SteeringAngle(0);
        if_drive = false;
    }

    virtual void drive(){}

    virtual void Restart(){}

    virtual char* Name(){}

    virtual void toggle_train(){}

    Car* car;
    bool if_drive;

};

#endif
