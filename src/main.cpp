#include "engine.h"
#include "verlet_cloth_sim.h"

int main(int argc, char** argv) {
    Coink("Coink [DEMO] v0.1.1", 1280, 720);
    DebugRenderVerlet();
    DebugShowFPS();
    InitClothSim();

    while (ShouldNotQuit()) {
        LoopBegin();

        UpdateClothSim();

        LoopEnd();
    }

    Close();
    return 0;
}

