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

    double HorsePower(){return HORSEPOWERS;}
    double MaxSteeringAngle(){return MAX_STEER_ANGLE;}

private:
    const double MAX_STEER_ANGLE;
    const double STEER_SPEED;
    const double SIDEWAYS_FRICTION_FORCE;
    const double HORSEPOWERS;
    const b2Vec2 CAR_STARTING_POS;

    const b2Vec2 leftRearWheelPosition;
    const b2Vec2 rightRearWheelPosition;
    const b2Vec2 leftFrontWheelPosition;
    const b2Vec2 rightFrontWheelPosition;

    double engineSpeed;
    double steeringAngle;

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
