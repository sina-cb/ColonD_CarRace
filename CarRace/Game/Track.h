#ifndef TRACK_H
#define TRACK_H

#include <Box2D/Box2D.h>
#include <cmath>

class Track{

public:
    Track(b2World * world);

private:
    b2World* world;
};

#endif
