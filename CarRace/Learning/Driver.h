#ifndef DRIVER_H
#define DRIVER_H

#include "../Game/Car.h"

class Driver{

public:
    Driver(){

    }
    Driver(Car* car);

    virtual ~Driver(){
        delete car;
    }

    virtual void drive(){

    }

    Car* car;

};

#endif
