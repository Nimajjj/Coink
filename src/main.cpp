#include <iostream>
#include <SDL.h>
#include "engine/engine.h"
#include "cmath"

double w = 640; // for debug use only
double h = 480;


int main(int argc, char** argv) {
    srand(time(NULL));
    auto engine = Engine("Engine [core]", w, h, 60);
    engine.SetClearColor({43, 42, 51});


    Particle* p1 = engine.NewParticle(engine.NewTexture("C:\\dev\\GameEngine\\ressource\\image\\test.png"));
    p1->SetLifetime(95);
    p1->SetMaxParticle(500);
    p1->SetEmitDelay(1);
    p1->SetColor({0xD3, 0x34, 0x09, 155});
    p1->SetSize({12, 12});


    p1->SetOrigin({w / 3 - 8, h/5*4 - 8});
    p1->SetAcceleration({0, -0.15});
    p1->SetFriction({0, -.004});
    p1->SetStopAccel(30);
    p1->SetRotation(3);

    p1->SetRandomOrigin({16, 8});
    p1->SetRandomRotation(3);
    p1->SetRandomSize(2);
    p1->SetRandomFriction({0, -.002});
    p1->SetRandomAcceleration({.01, 0});


    Particle* p2 = engine.NewParticle(engine.NewTexture("C:\\dev\\GameEngine\\ressource\\image\\test.png"));
    p2->SetLifetime(95);
    p2->SetMaxParticle(500);
    p2->SetEmitDelay(1);
    p2->SetColor({0x3A, 0xA5, 0x51, 155});
    p2->SetSize({12, 12});


    p2->SetOrigin({w / 2 - 8, h/5*4 - 8});
    p2->SetAcceleration({0, -0.15});
    p2->SetFriction({0, -.004});
    p2->SetStopAccel(30);
    p2->SetRotation(3);

    p2->SetRandomOrigin({16, 8});
    p2->SetRandomRotation(3);
    p2->SetRandomSize(2);
    p2->SetRandomFriction({0, -.002});
    p2->SetRandomAcceleration({.01, 0});

    Particle* p3 = engine.NewParticle(engine.NewTexture("C:\\dev\\GameEngine\\ressource\\image\\test.png"));
    p3->SetLifetime(95);
    p3->SetMaxParticle(500);
    p3->SetEmitDelay(1);
    p3->SetColor({0xFF, 0xFF, 0xFF, 155});
    p3->SetSize({12, 12});

    p3->SetOrigin({w / 3 * 2 - 8, h/5*4 - 8});
    p3->SetAcceleration({0, -0.15});
    p3->SetFriction({0, -.004});
    p3->SetStopAccel(30);
    p3->SetRotation(3);

    p3->SetRandomOrigin({16, 8});
    p3->SetRandomRotation(3);
    p3->SetRandomSize(2);
    p3->SetRandomFriction({0, -.002});
    p3->SetRandomAcceleration({.01, 0});

    p1->SetEmitOccurence(4);
    p2->SetEmitOccurence(2);
    p3->SetEmitOccurence(1);

    unsigned x = 0;
    double elapsed_time = 0;
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


        //p1.velocity.x = cos(x * (std::numbers::pi / 180));
        //p2.velocity.x = cos(x * (std::numbers::pi / 180));
        //p3.velocity.x = cos(x * (std::numbers::pi / 180));
        //p1.velocity.y = sin(x * (std::numbers::pi / 180)) * 5;

        engine.Print("P1 : " + std::to_string(p1->particles_count), w/3 - 16, h/5*4 + 16, 16);
        engine.Print("P1 : " + std::to_string(p2->particles_count), w/2 - 16, h/5*4 + 16, 16);
        engine.Print("P1 : " + std::to_string(p3->particles_count), w/3*2 - 16, h/5*4 + 16, 16);

        engine.Print("particules : " + std::to_string(p1->particles_count + p2->particles_count + p3->particles_count), 8, 440, 24);


        engine.RenderEnd();
        engine.LoopEnd();
    }

    engine.Close();
    return 0;
}
