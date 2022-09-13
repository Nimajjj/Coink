//
// Created by Ben on 20/07/2022.
//

#include "physics_body.h"
#include <iostream>

PhysicsBody::PhysicsBody(const int& x, const int& y, const double& rad, const Color& col) :
    position( { (double)x, (double)y } ),
    position_old( { (double)x - 4, (double)y } ),
    radius(rad),
    color(col),
    acceleration({} )
{
    //std::cout << "new physic body : " << this << " " << position << " " << position_old << " " << acceleration << "\n";
}

void PhysicsBody::UpdatePosition(const double& delta) {
    const vec2 velocity = (position - position_old) * 0.999;
    position_old = position;

    // verlet integration
    position = position + velocity + acceleration * delta * delta;

    // reset acceleration
    acceleration = {};
}

void PhysicsBody::Accelerate(vec2 acc) {
    acceleration += acc;
}