#include <iostream>
#include <SDL.h>
#include "engine/engine.h"
#include "cmath"
#include "string"


int main(int argc, char** argv) {
    srand(time(NULL));
    Engine engine = {"Coink [core] v0.1.1", 1280, 720, 60};
    engine.SetClearColor({43, 42, 51});
    bool should_quit = false;

    VBody b0 = engine.NewVerletBody(100, 100, {4, 0});
    VBody b1 = engine.NewVerletBody(200, 100);
    VBody b2 = engine.NewVerletBody(200, 200);
    VBody b3 = engine.NewVerletBody(100, 200);

    engine.NewVerletStick(b0, b1);
    engine.NewVerletStick(b1, b2);
    engine.NewVerletStick(b2, b3);
    engine.NewVerletStick(b3, b0);
    engine.NewVerletStick(b3, b1);

    VBody b10 = engine.NewVerletBody(720, 200, {}, true);
    VBody b11 = engine.NewVerletBody(720 + 64 * 3, 200 + 50);
    VBody b12 = engine.NewVerletBody(720 + 128 * 3, 200, {0, -10});

    engine.NewVerletStick(b10, b11);
    engine.NewVerletStick(b11, b12);

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

        engine.RenderBegin();
        engine.RenderVerletBodies();

        if (engine.GetTime() - elapsed_time > 100) {
            engine.NewVerletBody(1280/2, 720/2, {(double)(rand() % 32), (double)(rand() % 32)});
            count++;
            elapsed_time = engine.GetTime();
        }


        std::string fps = std::to_string(engine.GetFramerate());
        engine.Print("FPS : " + fps, 32, 32, 24);
        engine.Print("Body count : " + std::to_string(count), 32, 32 + 32, 24);


        engine.RenderEnd();
        engine.LoopEnd();
    }

    engine.Close();
    return 0;
}
