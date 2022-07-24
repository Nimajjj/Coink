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
    Render(std::string name, int w, int h);
    ~Render();

    void Close();

    void Begin();
    void End(const Color& clear_color);

    SDL_Renderer*& Renderer();

    // drawing
    void DrawFillRect(int x, int y, int w, int h, Color color);
    void DrawRect(int x, int y, int w, int h, Color color);
    void DrawPixel(int x, int y, Color color);
    void DrawLine(int x1, int y1, int x2, int y2, Color color);


    // text
    void InitText(std::string file);
    void Print(std::string text, int x, int y, int size = 64);
    TTF_Font* Font() {return font;};

private:
    // rendering
    SDL_Window* window;
    SDL_Renderer* renderer;

    void init_sdl();
    void init_renderer();
    void init_window(std::string name);


    // text
    int font_size;
    TTF_Font* font;

};


#endif //GAMEENGINE_RENDER_H
