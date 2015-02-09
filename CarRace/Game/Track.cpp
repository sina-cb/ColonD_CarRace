#include "Track.h"
#include "Game.h"
#include <Box2D/Common/b2Math.h>

Track::Track(b2World *world)
{
    this->world = world;

    for (int i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        check_point_bodies[i] = 0;
    }

    create_track();
    create_checkpoints();
}

Track::~Track(){

}

void Track::create_checkpoints(){
    int* userD = new int[2];
    userD[0] = CHECKPOINT_USER_DATA;
    userD[1] = FINISH_LINE_USER_DATA;

    double check_points [][4] = {
        {6.0, -4.0, 6.0, 4.0},
        {8.0, -4.0, 8.0, 4.0},
        {10.0, -4.0, 10.0, 4.0},
        {12.0, -4.0, 12.0, 4.0},
        {14.0, -4.0, 14.0, 4.0},
        {16.0, -4.0, 16.0, 4.0},
        {18.0, -4.0, 18.0, 4.0},
        {20.0, -4.0, 20.0, 4.0},
        {22.0, -4.0, 22.0, 4.0},
        {24.0, -4.0, 22.0, 4.0},
        {26.0, -4.0, 22.0, 4.0},
        {28.0, -2.0, 22.0, 4.0},
        {30.0, -0.0, 22.0, 4.0},
        {32.0, 2.0, 22.0, 4.0},
        {32.0, 4.0, 22.0, 4.0},
        {32.0, 6.0, 22.0, 6.0},
        {32.0, 8.0, 22.0, 8.0},
        {32.0, 10.0, 22.0, 10.0},
        {30.0, 12.0, 22.0, 10.0},
        {28.0, 14.0, 22.0, 10.0},
        {26.0, 16.0, 22.0, 10.0},
        {26.0, 16.0, 20.0, 12.0},
        {26.0, 16.0, 18.0, 14.0},
        {26.0, 16.0, 18.0, 16.0},
        {26.0, 18.0, 18.0, 18.0},
        {26.0, 20.0, 18.0, 20.0},
        {26.0, 22.0, 18.0, 22.0},
        {26.0, 24.0, 18.0, 24.0},
        {26.0, 24.0, 18.0, 26.0},
        {27.5, 26.0, 19.0, 28.0},
        {29.0, 28.0, 20.0, 30.0},
        {30.5, 30.0, 21.0, 32.0},
        {32.0, 32.0, 22.0, 34.0},
        {32.0, 34.0, 22.0, 34.0},
        {32.0, 36.0, 22.0, 34.0},
        {30.66, 38.0, 22.0, 34.0},
        {29.33, 40.0, 22.0, 34.0},
        {28.0, 42.0, 22.0, 34.0},
        {26.0, 42.0, 22.0, 34.0},
        {24.0, 42.0, 22.0, 34.0},
        {22.0, 42.0, 22.0, 34.0},
        {20.0, 42.0, 20.0, 34.0},
        {18.0, 42.0, 18.0, 34.0},
        {16.0, 42.0, 16.0, 34.0},
        {14.0, 42.0, 14.0, 34.0},
        {12.0, 42.0, 12.0, 34.0},
        {10.0, 42.0, 10.0, 34.0},
        {8.0, 42.0, 8.0, 34.0},
        {6.0, 42.0, 6.0, 34.0},
        {4.0, 42.0, 4.0, 34.0},
        {2.0, 42.0, 2.0, 34.0},
        {0.0, 42.0, 0.0, 34.0},
        {-2.0, 42.0, -2.0, 34.0},
        {-4.0, 42.0, -4.0, 34.0},
        {-6.0, 42.0, -6.0, 34.0},
        {-8.0, 42.0, -8.0, 34.0},
        {-10.0, 42.0, -10.0, 34.0},
        {-12.0, 42.0, -12.0, 34.0},
        {-14.0, 42.0, -14.0, 34.0},
        {-16.0, 42.0, -14.0, 34.0},
        {-18.0, 42.0, -14.0, 34.0},
        {-20.0, 42.0, -14.0, 34.0},
        {-20.85, 40.0, -14.0, 34.0},
        {-21.7, 38.0, -14.66, 33.0},
        {-22.55, 36.0, -15.32, 32.0},
        {-23.4, 34.0, -15.98, 31.0},
        {-24.25, 32.0, -16.64, 30.0},
        {-25.1, 30.0, -17.3, 29.0},
        {-26.0, 28.0, -18.0, 28.0},
        {-26.0, 26.0, -18.0, 26.0},
        {-26.0, 24.0, -18.0, 24.0},
        {-24.67, 22.0, -16.67, 22.67},
        {-23.34, 20.0, -15.34, 21.34},
        {-22.0, 18.0, -14.0, 20.0},
        {-22.0, 18.0, -14.0, 18.0},
        {-22.0, 18.0, -14.0, 16.0},
        {-23.33, 16.0, -15.33, 14.67},
        {-24.66, 14.0, -16.66, 13.34},
        {-26.0, 12.0, -18.0, 12.0},
        {-26.0, 12.0, -18.0, 12.0},
        {-26.0, 10.0, -18.0, 10.0},
        {-26.0, 8.0, -18.0, 8.0},
        {-26.0, 6.0, -18.0, 6.0},
        {-26.0, 4.0, -18.0, 4.0},
        {-26.0, 2.0, -18.0, 4.0},
        {-26.0, 0.0, -18.0, 4.0},
        {-26.0, -2.0, -18.0, 4.0},
        {-26.0, -4.0, -18.0, 4.0},
        {-24.0, -4.0, -18.0, 4.0},
        {-22.0, -4.0, -18.0, 4.0},
        {-20.0, -4.0, -18.0, 4.0},
        {-18.0, -4.0, -18.0, 4.0},
        {-16.0, -4.0, -16.0, 4.0},
        {-14.0, -4.0, -14.0, 4.0},
        {-12.0, -4.0, -12.0, 4.0},
        {-10.0, -4.0, -10.0, 4.0},
        {-8.0, -4.0, -8.0, 4.0},
        {-6.0, -4.0, -6.0, 4.0},
        {-4.0, -4.0, -4.0, 4.0},
        {-2.0, -4.0, -2.0, 4.0},
        {0.0, -4.0, 0.0, 4.0},
        //FINISH_LINE
        {2.0, -4.0, 0.0, 4.0}
    };

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = userD + 0;

    for (int32 i = 0; i < TRACK_CHECKPOINT_COUNT; i++){

        if (i == TRACK_CHECKPOINT_COUNT - 1){
            cout << "Create finish line" << endl;
            bodyDef.userData = userD + 1;
            bodyDef.type = b2_staticBody;
        }

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
        fixtureDef->filter.categoryBits = Game::CHECKPOINT;
        fixtureDef->filter.maskBits = Game::BODY | Game::WHEEL;
        checkPoint->CreateFixture(fixtureDef);
    }
}

void Track::create_track(){
    b2BodyDef bd;
    b2Body* track = world->CreateBody(&bd);

    int OUTER_POINTS_COUNT = 16;
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

    for (int32 i = 0; i < OUTER_POINTS_COUNT - 1; i++){
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

    int INNER_POINTS_COUNT = 14;
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

    for (int32 i = 0; i < INNER_POINTS_COUNT - 1; i++){
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

void Track::DestroyBody(b2Body* body){
    for (int i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        if (check_point_bodies[i] == body){
            world->DestroyBody(body);
            check_point_bodies[i] = 0;
        }
    }
}

void Track::Restart(){
    for (int i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        if (check_point_bodies[i] != 0){
            world->DestroyBody(check_point_bodies[i]);
            check_point_bodies[i] = 0;
        }
    }

    create_checkpoints();
}
