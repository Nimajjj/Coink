//
// Created by Ben on 20/07/2022.
//

#include "physics.h"
#include<iostream>
#include <math.h>
#include <stdlib.h>


void Physics::Update(const double& delta) {
    const unsigned sub_steps = 4;
    const double sub_dt = delta / static_cast<double>(sub_steps);

    for (unsigned i = sub_steps; i--;) {
        apply_gravity();
        apply_constraint();
        solve_colisions();
        update_position(sub_dt);
    }
}

PhysicsBody* Physics::NewBody(const int& x, const int& y, const double& rad, const Color& col) {
    physics_bodies.push_back(PhysicsBody(x, y, rad, col));
    return &physics_bodies.back();
}

void Physics::apply_gravity() {
    for (auto& body : physics_bodies) {
        body.Accelerate(gravity);
    }
}

void Physics::update_position(const double& delta) {
    for (auto& body : physics_bodies) {
        body.UpdatePosition(delta);
    }
}

void Physics::apply_constraint() {
    const vec2 position = {1280/2, 720/2};
    const double radius = 350.0;

    for (auto& body : physics_bodies) {
        const vec2 to_body = body.position - position;
        const double dist = sqrt((to_body.x * to_body.x) + (to_body.y * to_body.y));

        if (dist > radius - body.radius) { // 32 is default body size
            const vec2 n = to_body / dist;
            body.position = position + n * (radius - body.radius);
        }
    }
}

void Physics::solve_colisions() {
    unsigned i = 0;
    for (auto& body_1 : physics_bodies) {
        for (unsigned j = i + 1; j < physics_bodies.size(); ++j) {
            PhysicsBody& body_2 = physics_bodies[j];

            const vec2 collision_axis = body_1.position - body_2.position;
            const double dist = collision_axis.length();
            const double min_dist = body_1.radius + body_2.radius;

            if (dist < min_dist) {  // if two bodies overlap
                const vec2 n = collision_axis / dist;
                const double delta = min_dist - dist;

                vec2 offset = 0.5 * delta;
                offset *= n;

                body_1.position += offset;
                body_2.position -= offset;
            }
        }
        i++;
    }
}