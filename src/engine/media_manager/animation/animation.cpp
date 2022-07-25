//
// Created by Ben on 21/07/2022.
//

#include "animation.h"

Animation::Animation(Texture* t, const int& sz_x, const int& sz_y, const int& n_frames, const double& d) :
    texture(t),
    current_index(0),
    frame_size({(double)sz_x, (double)sz_y}),
    nb_frames(n_frames),
    delay(d)
{
    int nb_col = texture->GetSize().x / sz_x;
    int nb_row = texture->GetSize().y / sz_y;

    for ( unsigned y = 0; y < nb_row; y++ ) {
        for ( unsigned x = 0; x < nb_col; x++ ) {
            dstrects.push_back({
               (int)x * sz_x,
               (int)y * sz_y,
               sz_x,
               sz_y
            });
        }
    }
}

Animation::~Animation() {
    Delete();
}

void Animation::Delete() {
    texture->Delete();
}


void Animation::Update(const double& current_time) {
    if ( current_time - elapsed_time >= delay ) {
        elapsed_time = current_time;

        current_index++;
        if ( current_index >= nb_frames ) {
            current_index = 0;
        }
    }
}

vec2 Animation::GetFrameSize() {
    return frame_size;
}

Texture* Animation::GetTexture() {
    return texture;
}

SDL_Rect* Animation::GetCurrentRect() {
    return &dstrects[current_index];
}