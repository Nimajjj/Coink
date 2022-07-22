//
// Created by Ben on 20/07/2022.
//

#include "physics_body.h"

PhysicsBody::PhysicsBody(int x, int y, int w, int h) :
    position({(double)x, (double)y}),
    size({(double)w, (double)h}),
    velocity(vec2(0, 0)),
    acceleration(vec2(0, 0))
{}