#ifndef TRACK_H
#define TRACK_H

#include <Box2D/Box2D.h>
#include <cmath>

class Track{

public:
    Track(b2World * world);

    void create_track();
    void create_checkpoints();

    static const int TRACK_USER_DATA_VALUE = 3;
    static const int TRACK_CHECKPOINT_COUNT = 4;

private:
    b2World* world;

    b2Body* check_point_bodies[TRACK_CHECKPOINT_COUNT];

    static const int x_shift = -3;
    static const int y_shift = 0;
};

#endif
