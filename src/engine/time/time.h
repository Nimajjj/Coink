//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_TIME_H
#define GAMEENGINE_TIME_H
#include <SDL.h>

class Time {
public:
    Time(unsigned int f);
    ~Time() = default;

    void Update();
    void UpdateLate();

    const double& Delta() const { return delta; };

    const double& Now() const { return now; }

private:
    double delta;
    double now;
    double last;

    double frame_last;
    double frame_delay;
    double frame_time;

    unsigned int frame_rate;
    unsigned int frame_count;
};


#endif //GAMEENGINE_TIME_H
