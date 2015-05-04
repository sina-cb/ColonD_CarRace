#ifndef TRACK_SIMPLE_H
#define TRACK_SIMPLE_H

#include <Box2D/Box2D.h>
#include <cmath>
#include "Track.h"

class TrackSimple : public Track{

public:
    TrackSimple(b2World * world);
    virtual void create_checkpoints();
    virtual void create_track();
    virtual void Restart();

};

#endif
