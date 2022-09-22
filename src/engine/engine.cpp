//
// Created by Ben on 20/07/2022.
//

#include "engine.h"


// PRIVATE ---------------

// main objects
bool should_not_close = true;

// params
Color clear_color = {43, 42, 51};
bool debug_show_fps = false;
bool debug_render_verlet = false;

// containers
std::vector<Particle*> particles;


// functions
static void render_verlet_bodies(bool bodies) {
    for (auto& stick : GetVerletSticks()) {
        VerletBody* b0 = &GetVerletBodies()[stick.b0];
        VerletBody* b1 = &GetVerletBodies()[stick.b1];
        DrawLine(
                b0->position.x,
                b0->position.y,
                b1->position.x,
                b1->position.y,
                COLOR_WHITE
        );
    }
    if (bodies) {
        for (auto& body : GetVerletBodies()) {
            DrawFillCircle(body.position.x, body.position.y, 4, COLOR_RED);
        }
    }
}



// PUBLIC ---------------


// open - close
int CoinkNew(const std::string& wname, const int& w, const int& h, const int& fps) {
    RenderInit(wname, w, h);
    TimeInit(fps);
    MediaManagerInit();
    InitText("../ressource/font/NotoSans-Regular.ttf");
    GuiInit();
    SetClearColor(clear_color);

    return 0;
}

void CoinkClose() {
    GuiClose();
    RenderClose();
    MediaManagerClose();
}


// loop

bool ShouldNotQuit() {
    TimeUpdate();
    PhysicsUpdate(GetTimeDelta());
    UpdateAnimation(GetTime());
    UpdateButtons();

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

    
    Begin();

    for ( auto& particle : particles ) {        // move loop to particles solver
        particle->Update( Renderer() );
    }

    GuiDisplay();

    if (debug_show_fps) {
        ScreenPrint("FPS : " + std::to_string(GetFramerate()), 8, 8, 18);
    }

    if (debug_render_verlet) {
        render_verlet_bodies(false);
    }
}

void LoopEnd() {
    
    End( clear_color );
    TimeUpdateLate();
}


// render

void DrawTexture(Texture* texture, const int& x, const int& y) {
    SDL_Rect dstrect = SDL_Rect{ x, y, (int)texture->GetSize().x, (int)texture->GetSize().y };
    SDL_RenderCopy(
            Renderer(),
            texture->GetSDLTexture(),
            NULL,
            &dstrect
    );
}

void DrawAnimation(Animation* animation, const int& x, const int& y) {
    SDL_Rect dstrect = { x, y, (int)animation->GetFrameSize().x, (int)animation->GetFrameSize().y };
    SDL_RenderCopy(
            Renderer(),
            animation->GetTexture()->GetSDLTexture(),
            animation->GetCurrentRect(),
            &dstrect
    );
}


// settings

void SetClearColor(Color col) {
    clear_color = col;
}


// particles

Particle* NewParticle(Texture* texture) {
    particles.push_back( new Particle(texture->GetSDLTexture()) );
    return particles.back();
}


// debug

void DebugRenderVerlet() {
    debug_render_verlet = !debug_render_verlet;
}

void DebugShowFPS() {
    debug_show_fps = !debug_show_fps;
}








