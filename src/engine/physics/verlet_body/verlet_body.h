//
// Created by Ben on 15/09/2022.
//

#ifndef COINK_VERLET_BODY_H
#define COINK_VERLET_BODY_H
#include "../../types.h"

class VerletBody {
public:
    VerletBody(const double& x, const double& y, const vec2& vel = {0.0, 0.0}, const bool& pin = false);
    ~VerletBody() = default;

    vec2 position;
    vec2 position_old;
    vec2 acceleration;
    bool pinned;
};


#endif //COINK_VERLET_BODY_H
