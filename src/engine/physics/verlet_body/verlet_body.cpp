//
// Created by Ben on 15/09/2022.
//

#include "physics/verlet_body/verlet_body.h"

VerletBody::VerletBody(const double& x, const double& y, const vec2& vel, const bool& pin) :
    position({x, y}),
    position_old({x - vel.x, y - vel.y}),
    pinned(pin),
    acceleration({})
{}