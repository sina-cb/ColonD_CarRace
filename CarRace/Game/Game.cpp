#include "Game.h"
#include <iostream>
using namespace std;

Game::Game()
{
    m_world->SetGravity(b2Vec2(0.0, 0.0));

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
        cout << "Keyboard Left!!!" << endl;
        break;

        // Press right to pan right.
    case GLUT_KEY_RIGHT:
        car->Body()->SetAwake(true);
        car->SteeringAngle(-car->MaxSteeringAngle());
        cout << "Keyboard Right!!!" << endl;
        break;

        // Press down to pan down.
    case GLUT_KEY_DOWN:
        car->Body()->SetAwake(true);
        car->EngineSpeed(car->HorsePower());
        cout << "Keyboard Down!!!" << endl;
        break;

        // Press up to pan up.
    case GLUT_KEY_UP:
        car->Body()->SetAwake(true);
        car->EngineSpeed(-car->HorsePower());
        cout << "Keyboard Up!!!" << endl;
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
        cout << "Key Pressed!" << endl;
        break;
    default:
        break;
    }
}

void Game::Step(Settings* settings)
{
    car->Update();
    bool advanceRay = settings->pause == 0 || settings->singleStep;

    Test::Step(settings);
    m_debugDraw.DrawString(5, m_textLine, "Top-down car racing simulation!");
    m_textLine += 15;

    float32 L = 11.0f;
    b2Vec2 point1(0.0f, 10.0f);
    b2Vec2 d(L * cosf(m_angle), L * sinf(m_angle));
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
    else
    {
        m_debugDraw.DrawSegment(point1, point2, b2Color(0.8f, 0.8f, 0.8f));
    }
    if (advanceRay)
    {
        m_angle += 0.25f * b2_pi / 180.0f;
    }

#if 0
    // This case was failing.
    {
        b2Vec2 vertices[4];
        //vertices[0].Set(-22.875f, -3.0f);
        //vertices[1].Set(22.875f, -3.0f);
        //vertices[2].Set(22.875f, 3.0f);
        //vertices[3].Set(-22.875f, 3.0f);

        b2PolygonShape shape;
        //shape.Set(vertices, 4);
        shape.SetAsBox(22.875f, 3.0f);

        b2RayCastInput input;
        input.p1.Set(10.2725f,1.71372f);
        input.p2.Set(10.2353f,2.21807f);
        //input.maxFraction = 0.567623f;
        input.maxFraction = 0.56762173f;

        b2Transform xf;
        xf.SetIdentity();
        xf.position.Set(23.0f, 5.0f);

        b2RayCastOutput output;
        bool hit;
        hit = shape.RayCast(&output, input, xf);
        hit = false;

        b2Color color(1.0f, 1.0f, 1.0f);
        b2Vec2 vs[4];
        for (int32 i = 0; i < 4; ++i)
        {
            vs[i] = b2Mul(xf, shape.m_vertices[i]);
        }

        m_debugDraw.DrawPolygon(vs, 4, color);
        m_debugDraw.DrawSegment(input.p1, input.p2, color);
    }
#endif
}
