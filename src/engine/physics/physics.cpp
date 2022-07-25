//
// Created by Ben on 20/07/2022.
//

#include "physics.h"


void Physics::Update(const Time& time) {
    for (unsigned i = 0; i < physics_bodies.size(); i++) {
        PhysicsBody& body = physics_bodies[i];
        body.velocity += body.acceleration * time.Delta();
        body.position += body.velocity * time.Delta();
    }
}

PhysicsBody& Physics::NewBody(const int& x, const int& y, const int& w, const int& h) {
    PhysicsBody body = { x, y, w, h };
    physics_bodies.push_back(body);
    return physics_bodies[physics_bodies.size() - 1];
}