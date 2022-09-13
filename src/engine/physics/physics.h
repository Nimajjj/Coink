//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H
#include <vector>
#include "physics_body/physics_body.h"
#include "../time/time.h"

class Physics {
public:
    Physics(): gravity({0.0, 1000.0}) {};
    ~Physics() = default;

    void Update(const double& delta);

    PhysicsBody* NewBody(const int& x, const int& y, const double& rad, const Color& col = COLOR_GREEN);


    std::vector<PhysicsBody> physics_bodies;

private:
    vec2 gravity;

    void apply_gravity();
    void update_position(const double& delta);
    void apply_constraint();
    void solve_colisions();
};


#endif //GAMEENGINE_PHYSICS_H
