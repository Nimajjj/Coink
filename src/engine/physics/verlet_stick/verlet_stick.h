//
// Created by Ben on 15/09/2022.
//

#ifndef COINK_VERLET_STICK_H
#define COINK_VERLET_STICK_H
#include <math.h>
#include "../verlet_body/verlet_body.h"

/**
 * TODO :
 *  - Switch from VerletBody* b0 to VBody b0
 */

class VerletStick {
public:
    VerletStick(const VBody& body0, const VBody& body1);
    ~VerletStick() = default;

    VBody b0;
    VBody b1;
    double length;
};


#endif //COINK_VERLET_STICK_H
