//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_PHYSICS_BODY_H
#define GAMEENGINE_PHYSICS_BODY_H
#include "../../types.h"

class PhysicsBody {
public:
    PhysicsBody(int x, int y, int w, int h);
    ~PhysicsBody() = default;

    vec2 position;
    vec2 size;
    vec2 velocity;
    vec2 acceleration;
};


#endif //GAMEENGINE_PHYSICS_BODY_H
