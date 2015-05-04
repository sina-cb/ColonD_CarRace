#include "Track_Simple.h"
#include "Game.h"
#include <Box2D/Common/b2Math.h>

TrackSimple::TrackSimple(b2World * world){
    this->world = world;

    for (int i = 0; i < TRACK_CHECKPOINT_COUNT; i++){
        check_point_bodies[i] = 0;
    }

    create_track();
    create_checkpoints();
}

void TrackSimple::create_checkpoints(){
}

void TrackSimple::create_track(){
    b2BodyDef bd;
    b2Body* track = world->CreateBody(&bd);

    int OUTER_POINTS_COUNT = 6;
    double outer_track[][2] =  {
        {0.0, -4.0},
        {32.0, -4.0},
        {32.0, 42.0},
        {-26.0, 42.0},
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

    int INNER_POINTS_COUNT = 6;
    double inner_track[][2] =  {
        {0.0, 4.0},
        {22.0, 4.0},
        {22.0, 34.0},
        {-18.0, 34.0},
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

void TrackSimple::Restart(){

}
