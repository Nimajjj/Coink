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
    Physics() {};
    ~Physics() = default;

    void Update(const Time& time);

    PhysicsBody& NewBody(int x, int y, int w, int h);

private:
    std::vector<PhysicsBody> physics_bodies;
};


#endif //GAMEENGINE_PHYSICS_H
