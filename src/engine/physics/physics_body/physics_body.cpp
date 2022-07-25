//
// Created by Ben on 20/07/2022.
//

#include "physics_body.h"

PhysicsBody::PhysicsBody(const int& x, const int& y, const int& w, const int& h) :
    position( { (double)x, (double)y } ),
    size( { (double)w, (double)h } ),
    velocity( { 0, 0 } ),
    acceleration( { 0, 0 } )
{}