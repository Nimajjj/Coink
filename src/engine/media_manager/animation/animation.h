//
// Created by Ben on 21/07/2022.
//

#ifndef ENGINE_ANIMATION_H
#define ENGINE_ANIMATION_H
#include <vector>
#include <SDL.h>
#include "../texture/texture.h"


class Animation {
public:
    Animation(Texture* t, int sz_x, int sz_y, int n_frames, double d);
    ~Animation();

    void Delete();

    void Update(double current_time);

    vec2 GetFrameSize();
    Texture* GetTexture();
    SDL_Rect* GetCurrentRect();

private:
    Texture* texture;
    std::vector<SDL_Rect> dstrects;
    unsigned int current_index;
    double elapsed_time;
    vec2 frame_size;
    int nb_frames;
    double delay;
};


#endif //ENGINE_ANIMATION_H
