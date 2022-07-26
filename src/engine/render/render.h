//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_RENDER_H
#define GAMEENGINE_RENDER_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../types.h"
#include "../media_manager/media_manager.h"

class Render {
public:
    const int width;
    const int height;

    // init
    Render(const std::string& name, const int& w, const int& h);
    ~Render();
    void Close();

    void Begin();
    void End(const Color& clear_color);

    SDL_Renderer*& Renderer();
    SDL_Window*& Window();

    // drawing
    void DrawFillRect(const int& x, const int& y, const int& w, const int& h, Color color);
    void DrawRect(const int& x, const int& y, const int& w, const int& h, Color color);
    void DrawPixel(const int& x, const int& y, Color color);
    void DrawLine(const int& x1, const int& y1, const int& x2, const int& y2, Color color);


    // text
    void InitText(const std::string& file);
    void Print(const std::string& text, const int& x, const int& y, const int& size = 64);
    TTF_Font* Font() {return font;};

private:
    const int font_size;
    TTF_Font* font;

    SDL_Window* window;
    SDL_Renderer* renderer;

    void init_sdl();
    void init_renderer();
    void init_window(const std::string& name);
};


#endif //GAMEENGINE_RENDER_H
