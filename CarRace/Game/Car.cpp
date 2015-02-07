#include "Car.h"
#include <Box2D/Common/b2Math.h>

Car::Car(b2World *world): CAR_STARTING_POS(10, 10),
    leftRearWheelPosition(-1.5, 1.90),
    rightRearWheelPosition(1.5, 1.9),
    leftFrontWheelPosition(-1.5, -1.9),
    rightFrontWheelPosition(1.5, -1.9)
{
    this->world = world;

    engineSpeed = 0.0;
    steeringAngle = 0.0;

    b2BodyDef * staticDef = new b2BodyDef();
    staticDef->position.Set(5.0, 5.0);

    // define our body
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->linearDamping = 1;
    bodyDef->angularDamping = 1;
    bodyDef->position = CAR_STARTING_POS;

    body = world->CreateBody(bodyDef);
    body->ResetMassData();

    int* userD = new int[2];
    userD[0] = 1;
    userD[1] = 2;

    b2BodyDef* leftWheelDef = new b2BodyDef();
    leftWheelDef->type = b2_dynamicBody;
    leftWheelDef->position = CAR_STARTING_POS;
    leftWheelDef->position += leftFrontWheelPosition;
    leftWheelDef->userData = userD + 0;
    leftWheel = world->CreateBody(leftWheelDef);

    b2BodyDef* rightWheelDef = new b2BodyDef();
    rightWheelDef->type = b2_dynamicBody;
    rightWheelDef->position = CAR_STARTING_POS;
    rightWheelDef->position += rightFrontWheelPosition;
    rightWheelDef->userData = userD + 1;
    rightWheel = world->CreateBody(rightWheelDef);

    b2BodyDef* leftRearWheelDef = new b2BodyDef();
    leftRearWheelDef->type = b2_dynamicBody;
    leftRearWheelDef->position = CAR_STARTING_POS;
    leftRearWheelDef->position += leftRearWheelPosition;
    leftRearWheel = world->CreateBody(leftRearWheelDef);

    b2BodyDef* rightRearWheelDef = new b2BodyDef();
    rightRearWheelDef->type = b2_dynamicBody;
    rightRearWheelDef->position = CAR_STARTING_POS;
    rightRearWheelDef->position += rightRearWheelPosition;
    rightRearWheel = world->CreateBody(rightRearWheelDef);

    // define our shapes
    body = world->CreateBody(bodyDef);
    b2PolygonShape* boxDef = new b2PolygonShape();
    boxDef->SetAsBox(1.5, 2.5);
    body->CreateFixture(boxDef, 1);

    //Left Wheel shape
    leftWheel = world->CreateBody(leftWheelDef);
    b2PolygonShape* leftWheelShapeDef = new b2PolygonShape();
    leftWheelShapeDef->SetAsBox(0.2, 0.5);
    leftWheel->CreateFixture(leftWheelShapeDef, 1);

    //Right Wheel shape
    rightWheel = world->CreateBody(rightWheelDef);
    b2PolygonShape* rightWheelShapeDef = new b2PolygonShape();
    rightWheelShapeDef->SetAsBox(0.2, 0.5);
    rightWheel->CreateFixture(rightWheelShapeDef, 1);

    //Left Wheel shape
    leftRearWheel = world->CreateBody(leftRearWheelDef);
    b2PolygonShape* leftRearWheelShapeDef = new b2PolygonShape();
    leftRearWheelShapeDef->SetAsBox(0.2, 0.5);
    leftRearWheel->CreateFixture(leftRearWheelShapeDef, 1);

    //Right Wheel shape
    rightRearWheel = world->CreateBody(rightRearWheelDef);
    b2PolygonShape* rightRearWheelShapeDef = new b2PolygonShape();
    rightRearWheelShapeDef->SetAsBox(0.2, 0.5);
    rightRearWheel->CreateFixture(rightRearWheelShapeDef, 1);

    body->ResetMassData();
    leftWheel->ResetMassData();
    rightWheel->ResetMassData();
    leftRearWheel->ResetMassData();
    rightRearWheel->ResetMassData();

    b2RevoluteJointDef* leftJointDef = new b2RevoluteJointDef();
    leftJointDef->Initialize(body, leftWheel, leftWheel->GetWorldCenter());
    leftJointDef->enableMotor = true;
    leftJointDef->maxMotorTorque = 100;

    b2RevoluteJointDef* rightJointDef = new b2RevoluteJointDef();
    rightJointDef->Initialize(body, rightWheel, rightWheel->GetWorldCenter());
    rightJointDef->enableMotor = true;
    rightJointDef->maxMotorTorque = 100;

    leftJoint = (b2RevoluteJoint*)world->CreateJoint(leftJointDef);
    rightJoint = (b2RevoluteJoint*)world->CreateJoint(rightJointDef);

    b2PrismaticJointDef* leftRearJointDef = new b2PrismaticJointDef();
    leftRearJointDef->Initialize(body, leftRearWheel, leftRearWheel->GetWorldCenter(), b2Vec2(1, 0));
    leftRearJointDef->enableLimit = true;
    leftRearJointDef->lowerTranslation = leftRearJointDef->upperTranslation = 0;

    b2PrismaticJointDef* rightRearJointDef = new b2PrismaticJointDef();
    rightRearJointDef->Initialize(body, rightRearWheel, rightRearWheel->GetWorldCenter(), b2Vec2(1, 0));
    rightRearJointDef->enableLimit = true;
    rightRearJointDef->lowerTranslation = rightRearJointDef->upperTranslation = 0;

    world->CreateJoint(leftRearJointDef);
    world->CreateJoint(rightRearJointDef);

    body->SetTransform(b2Vec2(-10, 10), 0.0);
    leftWheel->SetTransform(b2Vec2(-10, 10), 0.0);
    rightWheel->SetTransform(b2Vec2(-10, 10), 0.0);
    leftRearWheel->SetTransform(b2Vec2(-10, 10), 0.0);
    rightRearWheel->SetTransform(b2Vec2(-10, 10), 0.0);
}

//This function applies a "friction" in a direction orthogonal to the body's axis.
void Car::killOrthogonalVelocity(b2Body* targetBody){
    b2Vec2 localPoint(0, 0);
    b2Vec2 velocity = targetBody->GetLinearVelocityFromLocalPoint(localPoint);

    b2Vec2 sidewaysAxis = targetBody->GetTransform().R.col2;
    sidewaysAxis *= b2Dot(velocity, sidewaysAxis);

    targetBody->SetLinearVelocity(sidewaysAxis);
}

void Car::Update(){
    world->Step(1.0 / 30.0, 8, 10);
    killOrthogonalVelocity(leftWheel);
    killOrthogonalVelocity(rightWheel);
    killOrthogonalVelocity(leftRearWheel);
    killOrthogonalVelocity(rightRearWheel);

    //Driving
    b2Vec2 ldirection = leftWheel->GetTransform().R.col2;
    ldirection *= engineSpeed;

    b2Vec2 rdirection = rightWheel->GetTransform().R.col2;
    rdirection *= engineSpeed;
    leftWheel->ApplyForce(ldirection, leftWheel->GetPosition());
    rightWheel->ApplyForce(rdirection, rightWheel->GetPosition());

    //Steering
    double mspeed;
    mspeed = steeringAngle - leftJoint->GetJointAngle();
    leftJoint->SetMotorSpeed(mspeed * STEER_SPEED);
    mspeed = steeringAngle - rightJoint->GetJointAngle();
    rightJoint->SetMotorSpeed(mspeed * STEER_SPEED);
}

b2Vec2 Car::SensorLocation(){
    b2Vec2 center = rightWheel->GetTransform().position + leftWheel->GetTransform().position;
    center.Set(center.x / 2.0, center.y / 2.0);
    return center;
}
