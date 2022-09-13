#include <iostream>
#include <SDL.h>
#include "engine/engine.h"
#include "cmath"
#include "string"



int main(int argc, char** argv) {
    srand(time(NULL));
    Engine engine = {"Coink [core] v0.1", 1280, 720, 60};
    engine.SetClearColor({43, 42, 51});

    //PhysicsBody* b1 = engine.NewPhysicsBody(500, 720/2);
    //PhysicsBody* b2 = engine.NewPhysicsBody(600, 720/2);
    //PhysicsBody* b3 = engine.NewPhysicsBody(700, 720/2);

    bool should_quit = false;
    double elapsed_time = 0.0;
    unsigned count = 0;

    while (!should_quit) {
        engine.LoopBegin();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;
            }
            break;
        }

        if (count < 400) {
            if (engine.GetTime() - elapsed_time > 30) {
                elapsed_time = engine.GetTime();
                engine.NewPhysicsBody(1280/2, 70, 8 + rand() % 16, {100 + rand() % 100, 100 + rand() % 100, 100 + rand() % 100});
                count++;
            }
        }


        engine.RenderBegin();
        engine.Draw(DRAW_CIRCLE, COLOR_WHITE, 1280/2, 720/2, 350);
        engine.RenderPhysicsBodies();

        std::string fps = "FPS : " + std::to_string(engine.GetFramerate());
        std::string bodies_count = "Bodies : " + std::to_string(count);
        engine.Print(fps, 16, 16, 32);
        engine.Print(bodies_count, 16, 16 + 32, 32);

        engine.RenderEnd();
        engine.LoopEnd();
    }

    engine.Close();
    return 0;
}
