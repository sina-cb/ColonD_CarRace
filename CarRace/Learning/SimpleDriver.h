#ifndef SIMPLE_DRIVER_H
#define SIMPLE_DRIVER_H

#include "Driver.h"

class SimpleDriver : public Driver{

public:
    SimpleDriver(Car* car);
    void drive();

private:
    int direction;
    double steer_value;

};

#endif
