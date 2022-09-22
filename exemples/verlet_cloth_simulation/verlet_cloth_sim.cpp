//
// Created by Ben on 21/09/2022.
//

#include "verlet_cloth_sim.h"

void InitClothSim(Engine& engine) {
    unsigned bodies_count = 0;
    unsigned sticks_count = 0;

    const unsigned width = 1280 / 8 / 5 * 4;
    const unsigned height = 720 / 14;
    const unsigned spacing = 8;
    const vec2 offset = {
            (1280 - (width * spacing)) / 2,
            0
    };
    VBody bodies[height][width];

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            bool pinned = (y == 0);
            vec2 vel = {};
            if (y <= height - 2) {
                vel = {(double)(rand() % 8), 0};
            }

            bodies[y][x] = engine.NewVerletBody(offset.x + x * spacing, offset.y + y * spacing, vel, pinned);

            bodies_count++;
        }
    }

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            if (y < height - 1) {
                engine.NewVerletStick(bodies[y][x], bodies[y+1][x]);
                sticks_count++;
            }

            if (x < width - 1) {
                engine.NewVerletStick(bodies[y][x], bodies[y][x+1]);
                sticks_count++;
            }
        }
    }

    std::cout << "Verlet bodies : " << bodies_count << "\n";
    std::cout << "Verlet sticks : " << sticks_count << "\n";
}

void UpdateClothSim(Physics& physics) {
    int x, y;
    unsigned z = 16;

    SDL_PumpEvents();
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);

    if ((mouse_state & SDL_BUTTON_LMASK) != 0) {
        std::vector<int> to_remove;

        for (unsigned i=0; i < physics.GetVerletSticks().size(); i++) {
            VerletBody& b0 = physics.GetVerletBodies()[physics.GetVerletSticks()[i].b0];
            VerletBody& b1 = physics.GetVerletBodies()[physics.GetVerletSticks()[i].b1];

            if (b0.position.x < x + z && b0.position.x > x - z &&
                b1.position.x < x + z && b1.position.x > x - z &&
                b0.position.y < y + z && b0.position.y > y - z &&
                b1.position.y < y + z && b1.position.y > y - z ) {
                to_remove.push_back(i);
            }

            i++;
        }

        for (int j : to_remove) {
            physics.GetVerletSticks().erase(physics.GetVerletSticks().begin() + j);
        }

    }
}