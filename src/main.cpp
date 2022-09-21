#include <cmath>
#include <iostream>
#include <string>
#include <SDL.h>
#include "engine.h"

#include "verlet_cloth_sim.h"


int main(int argc, char** argv) {
    srand(time(NULL));
    Engine engine = {"Coink v0.1.1", 1280, 720, 60};
    engine.DebugShowFPS();
    engine.DebugRenderVerlet();

    InitClothSim(engine);

    bool should_quit = false;
    while (!should_quit) {
        engine.LoopBegin(should_quit);

        UpdateClothSim(engine.GetPhysicsSolver());

        engine.RenderBegin();

        engine.RenderEnd();
        engine.LoopEnd();
    }

    engine.Close();
    return 0;
}

