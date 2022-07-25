//
// Created by Ben on 20/07/2022.
//

#include "engine.h"


// constructor

Engine::Engine(const std::string& wname, const int& w, const int& h, const int& fps) :
        render(Render(wname, w, h)),
        time(Time(fps)),
        physics(Physics()),
        clear_color({0x00, 0x00, 0x00})
{
    media_manager = MediaManager();
    render.InitText( "../ressource/font/NotoSans-Regular.ttf" );
    gui = GUI();
}

Engine::~Engine() {
    Close();
}

void Engine::Close() {
    gui.Close();
    render.Close();
    media_manager.Close();
}


// loop

void Engine::LoopBegin() {
    time.Update();
    physics.Update( time );
    media_manager.UpdateAnimation( GetTime() );
    gui.UpdateButtons();
}

void Engine::LoopEnd() {
    time.UpdateLate();
}


void Engine::RenderBegin() {
    render.Begin();

    for ( auto& particle : particles ) {
        particle->Update( render.Renderer() );
    }

    gui.Display( &render );
}

void Engine::RenderEnd() {
    render.End( clear_color );
}


// render

void Engine::Draw(const DRAW_TYPE& draw_type, const Color& col, const int& x, const int& y, const int& w, const int& h) {
    switch ( draw_type ) {
        case DRAW_FILL_RECT:
            render.DrawFillRect( x, y, w, h, col );
            break;

        case DRAW_RECT:
            render.DrawRect( x, y, w, h, col );
            break;

        case DRAW_LINE:
            render.DrawLine( x, y, w, h, col );
            break;

        case DRAW_PIXEL:
            render.DrawPixel( x, y, col );
            break;

        default:
            break;
    }
}

void Engine::Print(const std::string& text, const int& x, const int& y, const int& size) {
    render.Print( text, x, y, size );

}

void Engine::DrawPhysicsBody(PhysicsBody* body, const Color& col) {
    render.DrawRect(
            body->position.x,
            body->position.y,
            body->size.x,
            body->size.y,
            col
            );
    render.DrawLine(
            body->position.x,
            body->position.y,
            body->position.x + body->size.x - 1,
            body->position.y + body->size.y - 1,
            col
            );
}

void Engine::DrawTexture(Texture* texture, const int& x, const int& y) {
    SDL_Rect dstrect = SDL_Rect{ x, y, (int)texture->GetSize().x, (int)texture->GetSize().y };
    SDL_RenderCopy(
            render.Renderer(),
            texture->GetSDLTexture(),
            NULL,
            &dstrect
            );
}

void Engine::DrawAnimation(Animation* animation, const int& x, const int& y) {
    SDL_Rect dstrect = { x, y, (int)animation->GetFrameSize().x, (int)animation->GetFrameSize().y };
    SDL_RenderCopy(
            render.Renderer(),
            animation->GetTexture()->GetSDLTexture(),
            animation->GetCurrentRect(),
            &dstrect
            );
}


// physics

PhysicsBody* Engine::NewPhysicsBody(const int& x, const int& y, const int& w, const int& h) {
    return &physics.NewBody( x, y, w, h );
}


// settings

void Engine::SetClearColor(Color col) {
    clear_color = col;
}


// media

Texture* Engine::NewTexture(const char* file) {
    return media_manager.NewTexture(file, render.Renderer());
}

Animation* Engine::NewAnimation(Texture* t, const int& sz_x, const int& sz_y, const int& n_frames, const double& delay) {
    return media_manager.NewAnimation( t, sz_x, sz_y, n_frames, delay );
}


// time

double Engine::GetTime() {
    return time.Now();
}

double Engine::Delta() {
    return time.Delta();
}


// particles

Particle* Engine::NewParticle(Texture* texture) {
    particles.push_back( new Particle(texture->GetSDLTexture()) );
    return particles.back();
}


// gui

Button* Engine::ButtonNew(void (*act)(), const std::string& val, const unsigned& ft_size, const int& x, const int& y, const int& w, const int& h) {
    int width = w;
    int height = h;
    if ( w == 0 || h == 0 ) {
        SDL_Surface* surface = TTF_RenderText_Solid( render.Font(), val.c_str(), {0xFF,0xFF,0xFF} );
        double delta = ft_size / 64.0;
        if ( w == 0 ) {
            width = surface->w * delta + ft_size;
        }
        if (h == 0) {
            height = surface->h * delta;
        }
        SDL_FreeSurface( surface );
    }
    return gui.ButtonNew( act, val, ft_size, x, y ,width, height );
}

void Engine::ButtonDelete(Button* bt_to_delete) {
    gui.ButtonDelete( bt_to_delete );
}