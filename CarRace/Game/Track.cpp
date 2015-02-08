#include "Track.h"
#include "Game.h"
#include <Box2D/Common/b2Math.h>

Track::Track(b2World *world)
{
    this->world = world;

    create_track();
    create_checkpoints();

    for (int i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        check_point_bodies[i] = 0;
    }
}

void Track::create_checkpoints(){
    int* userD = new int[1];
    userD[0] = TRACK_USER_DATA_VALUE;

    int check_points [][4] = {
        {0.0, -4.0, 0.0, 4.0},
        //{2.0, -4.0, 2.0, 4.0},
        //{4.0, -4.0, 4.0, 4.0},
        {6.0, -4.0, 6.0, 4.0},
        {8.0, -4.0, 8.0, 4.0},
        {10.0, -4.0, 10.0, 4.0},
        {12.0, -4.0, 12.0, 4.0},
        {14.0, -4.0, 14.0, 4.0},
        {16.0, -4.0, 16.0, 4.0}
    };

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = userD + 0;

    for (int32 i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        if (check_point_bodies[i] != 0){
            world->DestroyBody(check_point_bodies[i]);
        }

        b2Body* checkPoint = world->CreateBody(&bodyDef);
        check_point_bodies[i] = checkPoint;

        b2PolygonShape shape;
        shape.SetAsEdge(b2Vec2(check_points[i][0] + x_shift, check_points[i][1] + y_shift),
                b2Vec2(check_points[i][2] + x_shift, check_points[i][3] + y_shift));
        b2FixtureDef* fixtureDef = new b2FixtureDef();
        fixtureDef->shape = &shape;
        fixtureDef->density = 0.0f;
        checkPoint->CreateFixture(fixtureDef);
    }
}

void Track::create_track(){
    int num_points = 16;
    double outer_track[][2] =  {
        {0.0, -4.0},
        {26.0, -4.0},
        {32.0, 2.0},
        {32.0, 10.0},
        {26.0, 16.0},
        {26.0, 24.0},
        {32.0, 32.0},
        {32.0, 36.0},
        {28.0, 42.0},
        {-20.0, 42.0},
        {-26.0, 28.0},
        {-26.0, 24.0},
        {-22.0, 18.0},
        {-26.0, 12.0},
        {-26.0, -4.0},
        {0.0, -4.0}
    };

    b2BodyDef bd;
    b2Body* track = world->CreateBody(&bd);

    for (int32 i = 0; i < num_points - 1; i++){
        b2PolygonShape shape;
        shape.SetAsEdge(b2Vec2(outer_track[i][0] + x_shift, outer_track[i][1] + y_shift),
                b2Vec2(outer_track[i + 1][0] + x_shift, outer_track[i + 1][1] + y_shift));
        b2FixtureDef* fixtureDef = new b2FixtureDef();
        fixtureDef->shape = &shape;
        fixtureDef->density = 0.0f;
        fixtureDef->filter.categoryBits = Game::BOUNDARY;
        fixtureDef->filter.maskBits = Game::BODY | Game::WHEEL;
        track->CreateFixture(fixtureDef);
    }

    num_points = 14;
    double inner_track[][2] =  {
        {0.0, 4.0},
        {22.0, 4.0},
        {22.0, 10.0},
        {18.0, 14.0},
        {18.0, 26.0},
        {22.0, 34.0},
        {-14.0, 34.0},
        {-18.0, 28.0},
        {-18.0, 24.0},
        {-14.0, 20.0},
        {-14.0, 16.0},
        {-18.0, 12.0},
        {-18.0, 4.0},
        {0.0, 4.0}
    };


    for (int32 i = 0; i < num_points - 1; i++){
        b2PolygonShape shape;
        shape.SetAsEdge(b2Vec2(inner_track[i][0] + x_shift, inner_track[i][1] + y_shift),
                b2Vec2(inner_track[i + 1][0] + x_shift, inner_track[i + 1][1] + y_shift));
        b2FixtureDef* fixtureDef = new b2FixtureDef();
        fixtureDef->shape = &shape;
        fixtureDef->density = 0.0f;
        fixtureDef->filter.categoryBits = Game::BOUNDARY;
        fixtureDef->filter.maskBits = Game::BODY | Game::WHEEL;
        track->CreateFixture(fixtureDef);
    }
}
