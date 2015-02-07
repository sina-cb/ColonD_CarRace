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
#include <cstring>

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
			if (index == 0)
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

    Game();

    void DestroyBody();
    void Keyboard(unsigned char key);
    void KeyboardSpecial(int key, int x, int y);
    void Step(Settings* settings);

    static Test* Create(){return new Game;}

	int32 m_bodyIndex;
	b2Body* m_bodies[e_maxBodies];
	int32 m_userData[e_maxBodies];
	b2PolygonShape m_polygons[4];
	b2CircleShape m_circle;

	float32 m_angle;

    Car *car;
};

#endif