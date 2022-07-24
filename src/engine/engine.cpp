//
// Created by Ben on 20/07/2022.
//

#include "engine.h"

Engine::Engine(std::string wname, int w, int h, int fps) :
        render(Render(wname, w, h)),
        time(Time(fps)),
        physics(Physics()),
        clear_color({0x00, 0x00, 0x00})
{
    render.InitText("../ressource/font/NotoSans-Regular.ttf");
    MediaManager::Init();
    gui = GUI();
}

Engine::~Engine() {
    Close();
}

void Engine::Close() {
    gui.Close();
    render.Close();
    MediaManager::Close();
}


void Engine::LoopBegin() {
    time.Update();
    physics.Update(time);
    MediaManager::UpdateAnimation(GetTime());
    gui.UpdateButtons();
}

void Engine::LoopEnd() {
    time.UpdateLate();
}


void Engine::RenderBegin() {
    render.Begin();

    for (auto particle : particles) {
        particle->Update(render.Renderer());
    }

    gui.Display(&render);
}

void Engine::RenderEnd() {
    render.End(clear_color);
}


// render

void Engine::Draw(DRAW_TYPE draw_type, Color col, int x, int y, int w, int h) {
    switch (draw_type) {
        case DRAW_FILL_RECT:
            render.DrawFillRect(x, y, w, h, col);
            break;

        case DRAW_RECT:
            render.DrawRect(x, y, w, h, col);
            break;

        case DRAW_LINE:
            render.DrawLine(x, y, w, h, col);
            break;

        case DRAW_PIXEL:
            render.DrawPixel(x, y, col);
            break;

        default:
            break;
    }
}

void Engine::Print(std::string text, int x, int y, int size) {
    render.Print(text, x, y, size);

}

void Engine::DrawPhysicsBody(PhysicsBody* body, Color col) {
    render.DrawRect(body->position.x, body->position.y, body->size.x, body->size.y, col);
    render.DrawLine(body->position.x, body->position.y,body->position.x + body->size.x - 1, body->position.y + body->size.y - 1, col);
}

void Engine::DrawTexture(Texture* texture, int x, int y) {
    SDL_Rect dstrect = SDL_Rect{ x, y, (int)texture->GetSize().x, (int)texture->GetSize().y };
    SDL_RenderCopy(
            render.Renderer(),
            texture->GetSDLTexture(),
            NULL,
            &dstrect
            );
}

void Engine::DrawAnimation(Animation* animation, int x, int y) {
    SDL_Rect dstrect = { x, y, (int)animation->GetFrameSize().x, (int)animation->GetFrameSize().y };
    SDL_RenderCopy(
            render.Renderer(),
            animation->GetTexture()->GetSDLTexture(),
            animation->GetCurrentRect(),
            &dstrect
            );
}


// physics

PhysicsBody* Engine::NewPhysicsBody(int x, int y, int w, int h) {
    return &physics.NewBody(x, y, w, h);
}


// settings

void Engine::SetClearColor(Color col) {
    clear_color = col;
}


// media

Texture* Engine::NewTexture(const char* file) {
    return MediaManager::NewTexture(file, render.Renderer());
}

Animation* Engine::NewAnimation(Texture* t, int sz_x, int sz_y, int n_frames, double delay) {
    return MediaManager::NewAnimation(t, sz_x, sz_y, n_frames, delay);
}


// time

double Engine::GetTime() {
    return time.Now();
}


// particles

Particle* Engine::NewParticle(Texture* texture) {
    particles.push_back(new Particle(texture->GetSDLTexture()));
    return particles.back();
}


// gui
Button* Engine::ButtonNew(void (*act)(), std::string val, unsigned ft_size, int x, int y, int w, int h) {  // move delta calculation here
    int width = w;
    int height = h;
    if (w == 0 || h == 0) {
        SDL_Surface* surface = TTF_RenderText_Solid(render.Font(), val.c_str(), {255,255,255});
        double delta = ft_size / 64.0;
        if (w == 0) {
            width = surface->w * delta + ft_size;
        }
        if (h == 0) {
            height = surface->h * delta;
        }
        SDL_FreeSurface(surface);
    }
    return gui.ButtonNew(act, val, ft_size, x, y ,width, height);
}
