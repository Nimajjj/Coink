//
// Created by Ben on 20/07/2022.
//

#ifndef ENGINE_MEDIA_MANAGER_H
#define ENGINE_MEDIA_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "texture/texture.h"
#include "animation/animation.h"

namespace MediaManager {
    extern unsigned int rmask, gmask, bmask, amask;

    void Init();
    void Close();

    void UpdateAnimation(double current_time);

    Texture* NewTexture(const char* file, SDL_Renderer* renderer);

    Animation* NewAnimation(Texture* t, int sz_x, int sz_y, int n_frames, double delay);
};


#endif //ENGINE_MEDIA_MANAGER_H
