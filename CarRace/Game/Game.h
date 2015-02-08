/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef GAME_H
#define GAME_H

#include "Test.h"
#include "Car.h"
#include "Track.h"
#include <cstring>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/filestream.h>

using namespace std;

// This test demonstrates how to use the world ray-cast feature.
// NOTE: we are intentionally filtering one of the polygons, therefore
// the ray will always miss one type of polygon.

// This callback finds the closest hit. Polygon 0 is filtered.
class RayCastClosestCallback : public b2RayCastCallback
{
public:
    RayCastClosestCallback()
    {
        m_hit = false;
    }

    float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
                            const b2Vec2& normal, float32 fraction)
    {
        b2Body* body = fixture->GetBody();
        void* userData = body->GetUserData();
        if (userData)
        {
            int32 index = *(int32*)userData;
            if (index == 1 || index == 2)
            {
                // filter
                return -1.0f;
            }
        }

        m_hit = true;
        m_point = point;
        m_normal = normal;
        return fraction;
    }

    bool m_hit;
    b2Vec2 m_point;
    b2Vec2 m_normal;
};

class Game : public Test
{
public:

    enum
    {
        e_maxBodies = 256,
    };

    enum entityCategory {
        BOUNDARY    =   0x0001,
        WHEEL       =   0x0002,
        BODY        =   0x0004,
        CHECKPOINT  =   0x0008,
    };

    Game();

    void DestroyBody();
    void Keyboard(unsigned char key);
    void KeyboardSpecial(int key, int x, int y);
    void KeyboardUp(unsigned char key);
    void KeyboardSpecialUp(int key, int x, int y);
    void Step(Settings* settings);
    void Restart();

    static Test* Create(){return new Game;}

    b2Body* m_bodies[e_maxBodies];

    Car* car;
    Track* track;
};

#endif
