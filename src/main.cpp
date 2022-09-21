#include <iostream>
#include <SDL.h>
#include "cmath"
#include "string"
#include "engine.h"


int main(int argc, char** argv) {
    srand(time(NULL));
    Engine engine = {"Coink v0.1.1", 1280, 720, 60};
    engine.SetClearColor({43, 42, 51});
    bool should_quit = false;

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
        engine.RenderBegin();
        engine.RenderVerletBodies();


        engine.Print("FPS : " + std::to_string(engine.GetFramerate()), 16, 16, 24);
        engine.RenderEnd();
        engine.LoopEnd();
    }

    engine.Close();
    return 0;
}

