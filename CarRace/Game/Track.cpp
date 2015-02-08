#include "Track.h"
#include "Game.h"
#include <Box2D/Common/b2Math.h>

Track::Track(b2World *world)
{
    this->world = world;

    int x_shift = -3;
    int y_shift = 0;

    int num_points = 16;
    double outer_track[][2] =  { {0.0, -4.0},
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
        track->CreateFixture(&shape, 0.0f);
    }




    num_points = 14;
    double inner_track[][2] =  { {0.0, 4.0},
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
