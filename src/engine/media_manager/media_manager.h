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

class MediaManager {
public:
    MediaManager();
    ~MediaManager();

    void Close();

    Texture* NewTexture(const char* file, SDL_Renderer* renderer);

    void UpdateAnimation(const double& current_time);
    Animation* NewAnimation(Texture* t, const int& sz_x, const int& sz_y, const int& n_frames, const double& delay);

private:
    unsigned rmask, gmask, bmask, amask;

    std::vector<Texture*> textures;
    std::vector<Animation*> animations;
};


#endif //ENGINE_MEDIA_MANAGER_H
