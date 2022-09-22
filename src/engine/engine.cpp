//
// Created by Ben on 20/07/2022.
//

#include "engine.h"


// PRIVATE ---------------

// main objects
Render* render = nullptr;
MediaManager media_manager;
Time coink_time;
Physics physics;
GUI gui;
bool should_not_close = true;

// params
Color clear_color = {43, 42, 51};
bool debug_show_fps = false;
bool debug_render_verlet = false;

// containers
std::vector<Particle*> particles;


// functions
static void render_verlet_bodies(bool bodies) {
    if (render == nullptr) { return; }
    for (auto& stick : physics.GetVerletSticks()) {
        VerletBody* b0 = &physics.GetVerletBodies()[stick.b0];
        VerletBody* b1 = &physics.GetVerletBodies()[stick.b1];
        render->DrawLine(
                b0->position.x,
                b0->position.y,
                b1->position.x,
                b1->position.y,
                COLOR_WHITE
        );
    }
    if (bodies) {
        for (auto& body : physics.GetVerletBodies()) {
            render->DrawFillCircle(body.position.x, body.position.y, 4, COLOR_RED);
        }
    }
}



// PUBLIC ---------------


// open - close
int Coink(const std::string& wname, const int& w, const int& h, const int& fps) {
    render = new Render(wname, w, h);
    coink_time = Time(fps);
    physics = Physics();
    media_manager = MediaManager();
    render->InitText("../ressource/font/NotoSans-Regular.ttf");
    gui = GUI();
    SetClearColor(clear_color);

    return 0;
}

void Close() {
    gui.Close();
    if (render != nullptr) { render->Close(); }
    media_manager.Close();
}


// loop

bool ShouldNotQuit() {
    coink_time.Update();
    physics.Update(coink_time.Delta());
    media_manager.UpdateAnimation( GetTime() );
    gui.UpdateButtons();

    return should_not_close;
}

void LoopBegin() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                should_not_close = false;
                return;
        }
        break;
    }
    should_not_close = true;

    if (render == nullptr) { return; }
    render->Begin();

    for ( auto& particle : particles ) {        // move loop to particles solver
        particle->Update( render->Renderer() );
    }

    gui.Display( render );

    if (debug_show_fps) {
        Print("FPS : " + std::to_string(GetFramerate()), 8, 8, 18);
    }

    if (debug_render_verlet) {
        render_verlet_bodies(false);
    }
}

void LoopEnd() {
    if (render == nullptr) { return; }
    render->End( clear_color );
    coink_time.UpdateLate();
}


// render

void Draw(const DRAW_TYPE& draw_type, const Color& col, const int& x, const int& y, const int& w, const int& h) {
    if (render == nullptr) { return; }
    switch ( draw_type ) {
        case DRAW_FILL_RECT:
            render->DrawFillRect( x, y, w, h, col );
            break;

        case DRAW_RECT:
            render->DrawRect( x, y, w, h, col );
            break;

        case DRAW_LINE:
            render->DrawLine( x, y, w, h, col );
            break;

        case DRAW_PIXEL:
            render->DrawPixel( x, y, col );
            break;

        case DRAW_CIRCLE:
            render->DrawCircle( x, y, w, col );
            break;

        case DRAW_FILL_CIRCLE:
            render->DrawFillCircle( x, y, w, col );
            break;


        default:
            break;
    }
}

void Print(const std::string& text, const int& x, const int& y, const int& size) {
    if (render == nullptr) { return; }
    render->Print( text, x, y, size );
}

void DrawTexture(Texture* texture, const int& x, const int& y) {
    if (render == nullptr) { return; }
    SDL_Rect dstrect = SDL_Rect{ x, y, (int)texture->GetSize().x, (int)texture->GetSize().y };
    SDL_RenderCopy(
            render->Renderer(),
            texture->GetSDLTexture(),
            NULL,
            &dstrect
    );
}

void DrawAnimation(Animation* animation, const int& x, const int& y) {
    if (render == nullptr) { return; }
    SDL_Rect dstrect = { x, y, (int)animation->GetFrameSize().x, (int)animation->GetFrameSize().y };
    SDL_RenderCopy(
            render->Renderer(),
            animation->GetTexture()->GetSDLTexture(),
            animation->GetCurrentRect(),
            &dstrect
    );
}


// physics

Physics& GetPhysicsSolver() {
    return physics;
}

VBody NewVerletBody(const double& x, const double& y, const vec2& vel, const bool& pin) {
    return physics.NewVerletBody(x, y, vel, pin);
}

VStick NewVerletStick(const VBody& body0, const VBody& body1) {
    return  physics.NewVerletStick(body0, body1);
}


// settings

void SetClearColor(Color col) {
    clear_color = col;
}


// media

Texture* NewTexture(const char* file) {
    if (render == nullptr) { return nullptr; }
    return media_manager.NewTexture(file, render->Renderer());
}

Animation* NewAnimation(Texture* t, const int& sz_x, const int& sz_y, const int& n_frames, const double& delay) {
    return media_manager.NewAnimation( t, sz_x, sz_y, n_frames, delay );
}


// coink_time   (the variable "time" was alredy taken, sorry for that)

double GetTime() {
    return coink_time.Now();
}

double Delta() {
    return coink_time.Delta();
}

const unsigned int& GetFramerate() {
    return coink_time.FrameRate();
}


// particles

Particle* NewParticle(Texture* texture) {
    particles.push_back( new Particle(texture->GetSDLTexture()) );
    return particles.back();
}


// gui

Button* ButtonNew(void (*act)(), const std::string& val, const unsigned& ft_size, const int& x, const int& y, const int& w, const int& h) {
    if (render == nullptr) { return nullptr; }
    int width = w;
    int height = h;
    if ( w == 0 || h == 0 ) {
        SDL_Surface* surface = TTF_RenderText_Solid( render->Font(), val.c_str(), {0xFF,0xFF,0xFF} );
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

void ButtonDelete(Button* bt_to_delete) {
    gui.ButtonDelete( bt_to_delete );
}

void DebugRenderVerlet() {
    debug_render_verlet = !debug_render_verlet;
}

void DebugShowFPS() {
    debug_show_fps = !debug_show_fps;
}








