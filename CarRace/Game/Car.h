#ifndef CAR_H
#define CAR_H

#include <Box2D/Box2D.h>
#include <cmath>

class Car{

public:
    Car(b2World * world);

    void killOrthogonalVelocity(b2Body* targetBody);
    void Update();

    b2Body* Body(){return body;}
    double EngineSpeed(){return engineSpeed;}
    double SteeringAngle(){return steeringAngle;}

    void EngineSpeed(double engineSpeed){this->engineSpeed = engineSpeed;}
    void SteeringAngle(double steeringAngle){this->steeringAngle = steeringAngle;}
    void ForceStop();

    double HorsePower(){return HORSEPOWERS;}
    double MaxSteeringAngle(){return MAX_STEER_ANGLE;}

    b2Vec2 SensorLocation();
    double SensorRange(){return SENSOR_RANGE;}
    double* SensorData(){return sensor_data;}

    void SetLocation(float32 x, float32 y, float32 angle);

    static const int LEFT_WHEEL_USER_DATA = 1;
    static const int RIGHT_WHEEL_USER_DATA = 2;
    static const int SENSOR_COUNT = 5;

    static const float32 POSITIVE = 0.9;
    static const float32 NEGATIVE = 0.1;
    static const float32 NEUTRAL = 0.5;

    double* sensor_data;
    double true_output;

private:
    static const double MAX_STEER_ANGLE = M_PI / 4.0;
    static const double STEER_SPEED = 2; //default = 1.5
    static const double SIDEWAYS_FRICTION_FORCE = 100;
    static const double HORSEPOWERS = 60; //default = 40

    const b2Vec2 CAR_STARTING_POS;
    const b2Vec2 leftRearWheelPosition;
    const b2Vec2 rightRearWheelPosition;
    const b2Vec2 leftFrontWheelPosition;
    const b2Vec2 rightFrontWheelPosition;

    double engineSpeed;
    double steeringAngle;
    static const double SENSOR_RANGE = 8;

    b2World* world;

    b2Body* body;
    b2Body* leftWheel;
    b2Body* rightWheel;
    b2Body* leftRearWheel;
    b2Body* rightRearWheel;

    b2RevoluteJoint* leftJoint;
    b2RevoluteJoint* rightJoint;
};

#endif
