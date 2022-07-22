//
// Created by Ben on 20/07/2022.
//

#include "render.h"


// constructor & destructor

Render::Render(std::string name, int w, int h) :
    width(w),
    height(h),
    font_size(64),
    window(nullptr),
    renderer(nullptr),
    font(nullptr)
{
    init_sdl();
    init_window(name);
    init_renderer();
}

Render::~Render() {
    Close();
}


// init and close

void Render::Close() {
    if (font != nullptr) {
        TTF_CloseFont(font);
        TTF_Quit();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Render::init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) { std::cout << "SDL_Init(SDL_INIT_VIDEO) HAS FAILED: " << SDL_GetError() << std::endl; }
    else { std::cout << "SDL_Init(SDL_INIT_VIDEO) SUCCESS" << std::endl; }
}

void Render::init_window(std::string name) {
    window = SDL_CreateWindow(
            name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN
    );

    if (!window){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }
}

void Render::init_renderer() {
    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

// rendering

void Render::Begin() {
    SDL_RenderClear(renderer);
}

void Render::End(const Color& clear_color) {
    SDL_SetRenderDrawColor(renderer, clear_color.r, clear_color.g, clear_color.b, 255);
    SDL_RenderPresent(renderer);
}

SDL_Renderer*& Render::Renderer() {
    return renderer;
}


// drawing

void Render::DrawFillRect(int x, int y, int w, int h, Color color) {
    auto rect = new SDL_Rect{x, y, w, h};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, rect);

    delete rect;
}

void Render::DrawRect(int x, int y, int w, int h, Color color) {
    auto rect = new SDL_Rect{x, y, w, h};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, rect);

    delete rect;
}

void Render::DrawPixel(int x, int y, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Render::DrawLine(int x1, int y1, int x2, int y2, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


// text

void Render::InitText(std::string file) {
    TTF_Init();
    font = TTF_OpenFont(file.c_str(), font_size);
}

void Render::Print(std::string text, int x, int y, int size) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255,255,255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    double font_size_delta = (double)size / font_size;
    SDL_Rect dstrect = SDL_Rect{
        x,
        y,
        (int)(w * font_size_delta),
        (int)(h * font_size_delta)
    };

    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}