#include "Game.h"
#include <iostream>
using namespace std;

Game::Game()
{
    m_world->SetGravity(b2Vec2(0.0, 0.0));

    //Load the track
    {

        double track_points[][2] =  { {0.0, 0.0},
                                   {2.0, 0.0},
                                   {2.0, 1.3},
                                   {0.0, 1.3},
                                   {0.0, 0.0}
                                 };

        b2BodyDef bd;
        b2Body* track = m_world->CreateBody(&bd);

        for (int32 i = 0; i < 4; i++){
            b2PolygonShape shape;
            shape.SetAsEdge(b2Vec2(track_points[i][0] * 30 - 30, track_points[i][1]* 30),
                    b2Vec2(track_points[i + 1][0] * 30 - 30, track_points[i + 1][1] * 30));
            track->CreateFixture(&shape, 0.0f);
        }

    }

    car = new Car(m_world);

}

void Game::DestroyBody()
{
    for (int32 i = 0; i < e_maxBodies; ++i)
    {
        if (m_bodies[i] != NULL)
        {
            m_world->DestroyBody(m_bodies[i]);
            m_bodies[i] = NULL;
            return;
        }
    }
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
    case 's':
        car->EngineSpeed(0);
        car->SteeringAngle(0);
        cout << "Reset speed!" << endl;
        break;
    default:
        break;
    }
}

void Game::Step(Settings* settings)
{
    Test::Step(settings);

    car->Update();

    m_debugDraw.DrawString(5, m_textLine, "Top-down car racing simulation!");
    m_textLine += 15;

    for (int i = 0; i < 5; i++){
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
        }
    }

}
