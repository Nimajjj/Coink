void cloth_sim(Engine& engine) {
    unsigned bodies_count = 0;
    unsigned sticks_count = 0;

    const unsigned width = 1280 / 8 / 5 * 4;
    const unsigned height = 720 / 10;
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