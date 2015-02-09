#ifndef Q_DRIVER_H
#define Q_DRIVER_H

#include "Driver.h"
#include "fann.h"

class QDriver : public Driver{

public:
    QDriver(Car* car);
    void drive();
    void Restart();
    char* Name(){return "Q-Learner Driver";}

private:
    int direction;
    double steer_value;

};

#endif
