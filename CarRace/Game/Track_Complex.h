#ifndef TRACK_COMPLEX_H
#define TRACK_COMPLEX_H

#include <Box2D/Box2D.h>
#include <cmath>
#include "Track.h"

class TrackComplex : public Track{

public:
    TrackComplex(b2World * world);
    virtual void create_checkpoints();
    virtual void create_track();
    virtual void Restart();
};

#endif
