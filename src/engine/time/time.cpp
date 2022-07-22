//
// Created by Ben on 20/07/2022.
//

#include "time.h"

Time::Time(unsigned int f) :
    frame_rate(f),
    frame_delay(1000.0 / f)
{}


void Time::Update() {
    now = (double)SDL_GetTicks();
    delta = (now - last) / 1000.f;
    last = now;
    ++frame_count;

    if (now - frame_last >= 1000.f) {
        frame_rate = frame_count;
        frame_count = 0;
        frame_last = now;
    }
}

void Time::UpdateLate() {
    frame_time = (double)SDL_GetTicks() - now;

    if (frame_delay > frame_time) {
        SDL_Delay(frame_delay - frame_time);
    }
}