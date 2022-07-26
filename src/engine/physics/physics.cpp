//
// Created by Ben on 20/07/2022.
//

#include "physics/physics.h"


// PRIVATE ---------------

const vec2 GRAVITY = {0, 1000};
const double BOUNCE_FACTOR = 0.6;
const double FRICTION_FACTOR = 0.999;
const unsigned SUB_STEPS = 12;
const unsigned SCREEN_WIDTH = 1280;
const unsigned SCREEN_HEIGHT = 720;

std::vector<VerletBody> verlet_bodies = {};
std::vector<VerletStick> verlet_sticks = {};

void update_bodies(const double& delta) {
    for (auto& body : verlet_bodies) {
        if (!body.pinned) {
            vec2 velocity = body.position - body.position_old;
            body.position_old = body.position;
            body.position += velocity + body.acceleration * FRICTION_FACTOR * delta * delta;

            body.acceleration = {};

            body.acceleration += GRAVITY;
        }
    }
}

void update_sticks() {
    for (auto& stick : verlet_sticks) {
        VerletBody* b0 = &verlet_bodies[stick.b0];
        VerletBody* b1 = &verlet_bodies[stick.b1];

        const vec2 d = b1->position - b0->position;
        const double distance = sqrt(d.x * d.x + d.y * d.y);
        const double difference = stick.length - distance;
        const double percent = difference / distance / 2.0;
        const vec2 offset = d * percent;

        if (!b0->pinned) {
            b0->position -= offset;
        }

        if (!b1->pinned) {
            b1->position += offset;
        }
    }
}

void constrain_bodies() {
    for (auto& body : verlet_bodies) {
        if (!body.pinned) {
            vec2 velocity = (body.position - body.position_old) * FRICTION_FACTOR;

            if (body.position.x > SCREEN_WIDTH) {
                body.position.x = SCREEN_WIDTH;
                body.position_old.x = body.position.x + velocity.x * BOUNCE_FACTOR;
            } else if (body.position.x < 0) {
                body.position.x = 0;
                body.position_old.x = body.position.x + velocity.x * BOUNCE_FACTOR;
            }

            if (body.position.y > SCREEN_HEIGHT) {
                body.position.y = SCREEN_HEIGHT;
                body.position_old.y = body.position.y + velocity.y * BOUNCE_FACTOR;
            } else if (body.position.y < 0) {
                body.position.y = 0;
                body.position_old.y = body.position.y + velocity.y * BOUNCE_FACTOR;
            }
        }
    }
}


// PUBLIC ---------------

void PhysicsUpdate(const double& delta) {
    double sub_delta = delta / (double)SUB_STEPS;

    for (unsigned  i = SUB_STEPS; i--;) {
        update_bodies(sub_delta);
        update_sticks();
        constrain_bodies();
    }
}


VBody NewVerletBody(const double& x, const double& y, const vec2& vel, const bool& pin) {
    verlet_bodies.push_back({x, y, vel, pin});
    return verlet_bodies.size() - 1;
}

VStick NewVerletStick(const VBody& body0, const VBody& body1) {
    verlet_sticks.push_back({body0, body1});

    const vec2 d = verlet_bodies[body0].position - verlet_bodies[body1].position;
    verlet_sticks[verlet_sticks.size() - 1].length = sqrt(d.x * d.x + d.y * d.y);

    return verlet_sticks.size() - 1;
}


std::vector<VerletBody>& GetVerletBodies() {
    return verlet_bodies;
}

std::vector<VerletStick>& GetVerletSticks() {
    return verlet_sticks;
}