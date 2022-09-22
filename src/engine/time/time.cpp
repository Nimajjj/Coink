//
// Created by Ben on 20/07/2022.
//

#include "time/time.h"

double delta;
double now;
double last;

double frame_last;
double frame_delay;
double frame_time;

unsigned int frame_rate;
unsigned int frame_count;

void TimeInit(const unsigned& f) {
    frame_rate = f;
    frame_delay = 1000.0 / f;
}

void TimeUpdate() {
    now = (double)SDL_GetTicks();
    delta = ( now - last ) / 1000.0;
    last = now;
    ++frame_count;

    if ( now - frame_last >= 1000.0 ) {
        frame_rate = frame_count;
        frame_count = 0;
        frame_last = now;
    }
}

void TimeUpdateLate() {
    frame_time = (double)SDL_GetTicks() - now;

    if ( frame_delay > frame_time ) {
        SDL_Delay( frame_delay - frame_time );
    }
}

const double& GetTimeDelta() { return delta; };
const double& GetTime() { return now; }
const unsigned int& GetFramerate() { return frame_rate; }