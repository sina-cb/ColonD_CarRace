#include "Track_Complex.h"
#include "Game.h"
#include <Box2D/Common/b2Math.h>

TrackComplex::TrackComplex(b2World * world){
    this->world = world;

    for (int i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        check_point_bodies[i] = 0;
    }

    create_track();
    create_checkpoints();
}

void TrackComplex::create_checkpoints(){

}

void TrackComplex::create_track(){
    b2BodyDef bd;
    b2Body* track = world->CreateBody(&bd);

    int OUTER_POINTS_COUNT = 22;
    double outer_track[][2] =  {
        {-20.50, -3.50},
        {24.57, -3.63},
        {30.81, 0.72},
        {31.56, 3.17},
        {30.85, 5.26},
        {30.11, 9.61},
        {31.56, 14.09},
        {30.98, 20.65},
        {31.56, 24.09},
        {27.73, 37.15},
        {20.48, 37.23},
        {12.62, 33.10},
        {08.75, 28.32},
        {12.79, 22.00},
        {14.95, 22.00},
        {11.08, 17.16},
        {07.13, 21.88},
        {-3.19, 41.69},
        {-12.80, 35.68},
        {-15.18, 22.80},
        {-23.80, 12.00},
        {-20.50, -3.50}
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

    int INNER_POINTS_COUNT = 18;
    double inner_track[][2] =  {
        {-14.1803030303,	4.28},
        {21.4106060606, 3.0533333333},
        {23.3212121212, 5.2613333333},
        {24.2,	9.8},
        {24.3984848485,	14.032},
        {25.8590909091,	24.0906666667},
        {24.5303030303,	28.4693333333},
        {19.7848484848,	30.592},
        {20.2484848485,	28.5066666667},
        {21.1909090909,	24.152},
        {17.5,	14.3386666667},
        {11.8318181818,	8.6346666667},
        {4.7575757576,	10.8426666667},
        {1.5939393939,	18.3866666667},
        {-3.9424242424,	31.7386666667},
        {-7.9409090909,	29.488},
        {-9.3909090909,	16.9146666667},
        {-14.1803030303,	4.28}
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

void TrackComplex::Restart(){

}
