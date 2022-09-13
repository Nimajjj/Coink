//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_PHYSICS_BODY_H
#define GAMEENGINE_PHYSICS_BODY_H
#include "../../types.h"

class PhysicsBody {
public:
    ~PhysicsBody() = default;
    PhysicsBody(const int& x, const int& y, const double& rad, const Color& col = COLOR_GREEN);

    vec2 position;
    vec2 position_old;
    vec2 acceleration;
    double radius;
    Color color;

    void UpdatePosition(const double& delta);
    void Accelerate(vec2 acc);
};


#endif //GAMEENGINE_PHYSICS_BODY_H
