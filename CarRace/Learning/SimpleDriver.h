#ifndef SIMPLE_DRIVER_H
#define SIMPLE_DRIVER_H

#include "Driver.h"
#include "fann.h"

class SimpleDriver : public Driver{

public:
    SimpleDriver(Car* car);
    void drive();
    void Restart();

private:
    int direction;
    double steer_value;

};

#endif
