#include "engine.h"
#include "verlet_cloth_sim.h"

int main(int argc, char** argv) {
    Engine engine = {"Coink [DEMO] v0.1.1", 1280, 720, 60};
    engine.DebugRenderVerlet();

    InitClothSim(engine);

    while (engine.ShouldNotQuit()) {
        engine.LoopBegin();

        UpdateClothSim(engine.GetPhysicsSolver());
        engine.Print("Hello Coink!", 0, 0, 32);

        engine.LoopEnd();
    }

    engine.Close();
    return 0;
}

