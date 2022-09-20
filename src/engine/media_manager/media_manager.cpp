//
// Created by Ben on 20/07/2022.
//

#include "media_manager/media_manager.h"

/*
 * TODO :
 *  - Remove MediaManager namspace and pu everything into the Texture class
 */


MediaManager::MediaManager() {
    if ( !(IMG_Init(IMG_INIT_PNG)) ) {
        std::cout << "IMG_Init HAS FAILED: " << SDL_GetError() << "\n";
    } else {
        std::cout << "IMG_Init(IMG_INIT_PNG) SUCCESS" << "\n";
    }

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
    #else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
    #endif
}

MediaManager::~MediaManager() {
    Close();
}

void MediaManager::Close() {
    for ( auto& texture: textures ) {
        delete texture;
        texture = nullptr;
    }

    for ( auto& animation: animations ) {
        delete animation;
        animation = nullptr;
    }
}


Texture* MediaManager::NewTexture(const char* file, SDL_Renderer* renderer) {
    SDL_Texture* sdl_texture =  IMG_LoadTexture( renderer, file );

    if ( sdl_texture == NULL ) {
        std::cout << "Texture failed to load: " << SDL_GetError() << "\n";
        return NULL;
    }

    textures.push_back( new Texture(sdl_texture) );
    return textures[textures.size() - 1];
}


void MediaManager::UpdateAnimation(const double& current_time) {
    for ( auto& animation: animations ) {
        animation->Update( current_time );
    }
}

Animation* MediaManager::NewAnimation(Texture* t, const int& sz_x, const int& sz_y, const int& n_frames, const double& delay) {
    animations.push_back(new Animation(
            t,
            sz_x,
            sz_y,
            n_frames,
            delay
            ));
    return animations[animations.size() - 1];
}
