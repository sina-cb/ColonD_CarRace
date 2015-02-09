#include "Car.h"
#include "Game.h"
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
    true_output = NEUTRAL;

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
    userD[0] = LEFT_WHEEL_USER_DATA;
    userD[1] = RIGHT_WHEEL_USER_DATA;

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
    b2FixtureDef* bodyFix = new b2FixtureDef();
    bodyFix->shape = boxDef;
    bodyFix->density = 1.0;
    bodyFix->filter.categoryBits = Game::BODY;
    bodyFix->filter.maskBits = Game::BOUNDARY | Game::CHECKPOINT;
    body->CreateFixture(bodyFix);

    //Left Wheel shape
    leftWheel = world->CreateBody(leftWheelDef);
    b2PolygonShape* leftWheelShapeDef = new b2PolygonShape();
    leftWheelShapeDef->SetAsBox(0.2, 0.5);
    b2FixtureDef* leftWheelFix = new b2FixtureDef();
    leftWheelFix->shape = leftWheelShapeDef;
    leftWheelFix->density = 1.0;
    leftWheelFix->filter.categoryBits = Game::WHEEL;
    leftWheelFix->filter.maskBits = Game::BOUNDARY | Game::CHECKPOINT;
    leftWheel->CreateFixture(leftWheelFix);

    //Right Wheel shape
    rightWheel = world->CreateBody(rightWheelDef);
    b2PolygonShape* rightWheelShapeDef = new b2PolygonShape();
    rightWheelShapeDef->SetAsBox(0.2, 0.5);
    b2FixtureDef* rightWheelFix = new b2FixtureDef();
    rightWheelFix->shape = rightWheelShapeDef;
    rightWheelFix->density = 1.0;
    rightWheelFix->filter.categoryBits = Game::WHEEL;
    rightWheelFix->filter.maskBits = Game::BOUNDARY | Game::CHECKPOINT;
    rightWheel->CreateFixture(rightWheelFix);

    //Left Wheel shape
    leftRearWheel = world->CreateBody(leftRearWheelDef);
    b2PolygonShape* leftRearWheelShapeDef = new b2PolygonShape();
    leftRearWheelShapeDef->SetAsBox(0.2, 0.5);
    b2FixtureDef* leftRearWheelFix = new b2FixtureDef();
    leftRearWheelFix->shape = leftRearWheelShapeDef;
    leftRearWheelFix->density = 1.0;
    leftRearWheelFix->filter.categoryBits = Game::WHEEL;
    leftRearWheelFix->filter.maskBits = Game::BOUNDARY | Game::CHECKPOINT;
    leftRearWheel->CreateFixture(leftRearWheelFix);

    //Right Wheel shape
    rightRearWheel = world->CreateBody(rightRearWheelDef);
    b2PolygonShape* rightRearWheelShapeDef = new b2PolygonShape();
    rightRearWheelShapeDef->SetAsBox(0.2, 0.5);
    b2FixtureDef* rightRearWheelFix = new b2FixtureDef();
    rightRearWheelFix->shape = rightRearWheelShapeDef;
    rightRearWheelFix->density = 1.0;
    rightRearWheelFix->filter.categoryBits = Game::WHEEL;
    rightRearWheelFix->filter.maskBits = Game::BOUNDARY | Game::CHECKPOINT;
    rightRearWheel->CreateFixture(rightRearWheelFix);

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

    sensor_data = new double[SENSOR_COUNT];
}

void Car::SetLocation(float32 x, float32 y, float32 angle){
    body->SetTransform(b2Vec2(x, y), angle);
    leftWheel->SetTransform(b2Vec2(x, y), angle);
    rightWheel->SetTransform(b2Vec2(x, y), angle);
    leftRearWheel->SetTransform(b2Vec2(x, y), angle);
    rightRearWheel->SetTransform(b2Vec2(x, y), angle);
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

void Car::ForceStop(){
    float desiredVel = 0;

    //////////////////// Stop the Body ////////////////////
    b2Vec2 vel = body->GetLinearVelocity();
    float velChange = desiredVel - vel.x;
    float impulse = body->GetMass() * velChange; //disregard time factor
    body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());

    velChange = desiredVel - vel.y;
    impulse = body->GetMass() * velChange; //disregard time factor
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter());

    //////////////////// Stop the left wheel ////////////////////
    vel = leftWheel->GetLinearVelocity();
    velChange = desiredVel - vel.x;
    impulse = leftWheel->GetMass() * velChange; //disregard time factor
    leftWheel->ApplyLinearImpulse(b2Vec2(impulse, 0), leftWheel->GetWorldCenter());

    velChange = desiredVel - vel.y;
    impulse = leftWheel->GetMass() * velChange; //disregard time factor
    leftWheel->ApplyLinearImpulse(b2Vec2(0, impulse), leftWheel->GetWorldCenter());

    //////////////////// Stop the right wheel ////////////////////
    vel = rightWheel->GetLinearVelocity();
    velChange = desiredVel - vel.x;
    impulse = rightWheel->GetMass() * velChange; //disregard time factor
    rightWheel->ApplyLinearImpulse(b2Vec2(impulse, 0), rightWheel->GetWorldCenter());

    velChange = desiredVel - vel.y;
    impulse = rightWheel->GetMass() * velChange; //disregard time factor
    rightWheel->ApplyLinearImpulse(b2Vec2(0, impulse), rightWheel->GetWorldCenter());

    //////////////////// Stop the left rear wheel ////////////////////
    vel = leftRearWheel->GetLinearVelocity();
    velChange = desiredVel - vel.x;
    impulse = leftRearWheel->GetMass() * velChange; //disregard time factor
    leftRearWheel->ApplyLinearImpulse(b2Vec2(impulse, 0), leftRearWheel->GetWorldCenter());

    velChange = desiredVel - vel.y;
    impulse = leftRearWheel->GetMass() * velChange; //disregard time factor
    leftRearWheel->ApplyLinearImpulse(b2Vec2(0, impulse), leftRearWheel->GetWorldCenter());

    //////////////////// Stop the right rear wheel ////////////////////
    vel = rightRearWheel->GetLinearVelocity();
    velChange = desiredVel - vel.x;
    impulse = rightRearWheel->GetMass() * velChange; //disregard time factor
    rightRearWheel->ApplyLinearImpulse(b2Vec2(impulse, 0), rightRearWheel->GetWorldCenter());

    velChange = desiredVel - vel.y;
    impulse = rightRearWheel->GetMass() * velChange; //disregard time factor
    rightRearWheel->ApplyLinearImpulse(b2Vec2(0, impulse), rightRearWheel->GetWorldCenter());

}
