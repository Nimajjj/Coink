//
// Created by Ben on 20/07/2022.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include <SDL_image.h>
#include "../../types.h"

class Texture {
public:
    Texture(SDL_Texture* t) :
        sdl_texture(t),
        size(vec2())
    {
        int w, h;
        SDL_QueryTexture(sdl_texture, NULL, NULL, &w, &h);
        size = vec2(w, h);
    };
    ~Texture() {
        Delete();
    };
    void Delete() {
        SDL_DestroyTexture(sdl_texture);
    }

    SDL_Texture* GetSDLTexture() const {return sdl_texture;};
    vec2 GetSize() const {return size;};

private:
    SDL_Texture* sdl_texture;
    vec2 size;

};


#endif //ENGINE_TEXTURE_H
