//
// Created by Ben on 15/09/2022.
//

#include "physics/verlet_stick/verlet_stick.h"

VerletStick::VerletStick(const VBody& body0, const VBody& body1) :
    b0(body0),
    b1(body1),
    length(0.0)
{}