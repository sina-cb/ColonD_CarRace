#ifndef ANN_DRIVER_H
#define ANN_DRIVER_H

#include "Driver.h"
#include "fann.h"
#include <iostream>
using namespace std;

class ANNDriver : public Driver{

public:
    ANNDriver(Car* car);
    void drive();
    void Restart();
    char* Name(){return "ANN Driver";}

private:



};

#endif
