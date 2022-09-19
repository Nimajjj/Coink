//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "../time/time.h"
#include "verlet_body/verlet_body.h"
#include "verlet_stick/verlet_stick.h"

class Physics {
public:
    Physics() {};
    ~Physics() = default;

    void Update(const double& delta);

    VBody NewVerletBody(const double& x, const double& y, const vec2& vel = {0.0, 0.0}, const bool& pin = false);
    VStick NewVerletStick(const VBody& body0, const VBody& body1);


    std::vector<VerletBody> verlet_bodies;
    std::vector<VerletStick> verlet_sticks;
private:


    void update_bodies(const double& delta);
    void update_sticks();
    void constrain_bodies();
};


#endif //GAMEENGINE_PHYSICS_H
