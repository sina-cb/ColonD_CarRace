#include "Game.h"
#include <iostream>
using namespace std;

Game::Game()
{
    m_world->SetGravity(b2Vec2(0.0, 0.0));
    track = new Track(m_world);
    car = new Car(m_world);
    car->SetLocation(0, 0, b2_pi / 2.0);
}

void Game::KeyboardSpecial(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_LEFT:
        car->Body()->SetAwake(true);
        car->SteeringAngle(car->MaxSteeringAngle());
        break;

        // Press right to pan right.
    case GLUT_KEY_RIGHT:
        car->Body()->SetAwake(true);
        car->SteeringAngle(-car->MaxSteeringAngle());
        break;

        // Press down to pan down.
    case GLUT_KEY_DOWN:
        car->Body()->SetAwake(true);
        car->EngineSpeed(car->HorsePower());
        break;

        // Press up to pan up.
    case GLUT_KEY_UP:
        car->Body()->SetAwake(true);
        car->EngineSpeed(-car->HorsePower());
        break;
    }
}

void Game::Keyboard(unsigned char key)
{
    switch (key)
    {

    default:
        break;
    }
}

void Game::KeyboardSpecialUp(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_LEFT:
        car->SteeringAngle(0);
        break;

        // Press right to pan right.
    case GLUT_KEY_RIGHT:
        car->SteeringAngle(0);
        break;

        // Press down to pan down.
    case GLUT_KEY_DOWN:
        car->EngineSpeed(0);
        break;

        // Press up to pan up.
    case GLUT_KEY_UP:
        car->EngineSpeed(0);
        break;
    }
}

void Game::KeyboardUp(unsigned char key){

}

void Game::Step(Settings* settings)
{
    Test::Step(settings);

    car->Update();

    m_debugDraw.DrawString(5, m_textLine, "Top-down car racing simulation!");
    m_textLine += 15;

    //Update sensor data
    for (int i = 0; i < Car::SENSOR_COUNT; i++){
        b2Vec2 point1 = car->SensorLocation();
        float32 angle = car->Body()->GetAngle() - (b2_pi / 4.0) * i;
        b2Vec2 d(car->SensorRange() * cosf(angle), car->SensorRange() * sinf(angle));
        b2Vec2 point2 = point1 + d;

        RayCastClosestCallback callback;
        m_world->RayCast(&callback, point1, point2);

        if (callback.m_hit)
        {
            m_debugDraw.DrawPoint(callback.m_point, 5.0f, b2Color(0.4f, 0.9f, 0.4f));
            m_debugDraw.DrawSegment(point1, callback.m_point, b2Color(0.8f, 0.8f, 0.8f));
            b2Vec2 head = callback.m_point + 0.5f * callback.m_normal;
            m_debugDraw.DrawSegment(callback.m_point, head, b2Color(0.9f, 0.9f, 0.4f));

            double dx = point1.x - callback.m_point.x;
            double dy = point1.y - callback.m_point.y;
            car->sensor_data[i] = sqrt(dx * dx + dy * dy);
        }else{
            car->sensor_data[i] = car->SensorRange();
        }
    }

    //Handle CheckPoint collisions
    static int iterations = 0;
    bool no_collision = true;
    for (int32 i = 0; i < m_pointCount; ++i)
    {
        ContactPoint* point = m_points + i;

        b2Body* body1 = point->fixtureA->GetBody();
        b2Body* body2 = point->fixtureB->GetBody();

        int32 index1 = 0;
        int32 index2 = 0;

        void* userData = body1->GetUserData();
        if (userData)
        {
            index1 = *(int32*)userData;
        }

        userData = body2->GetUserData();
        if (userData)
        {
            index2 = *(int32*)userData;
        }

        if (index1 == Track::CHECKPOINT_USER_DATA){
            track->DestroyBody(body1);
            car->true_output = car->POSITIVE;
            no_collision = false;
            return;
        }else if (index2 == Track::CHECKPOINT_USER_DATA){
            track->DestroyBody(body2);
            car->true_output = car->POSITIVE;
            no_collision = false;
            return;
        }

        cout << "Iteration " << iterations << ": Collided!" << endl;
        iterations++;
        car->true_output = car->NEGATIVE;
        no_collision = false;
        Restart();
        break;
    }

    if (no_collision){
        car->true_output = car->NEUTRAL;
    }

}

void Game::Restart(){
    car->ForceStop();
    car->SteeringAngle(0);
    car->EngineSpeed(0);
    car->SetLocation(0, 0, b2_pi / 2.0);

    track->Restart();
}
