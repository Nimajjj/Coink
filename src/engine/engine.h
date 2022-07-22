//
// Created by Ben on 20/07/2022.
//

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H
#include "render/render.h"
#include "time/time.h"
#include "physics/physics.h"
#include "media_manager/media_manager.h"
#include "particle/particle.h"

enum DRAW_TYPE {
    DRAW_RECT,
    DRAW_FILL_RECT,
    DRAW_LINE,
    DRAW_PIXEL
};

class Engine {
public:
    Engine(std::string wname, int w, int h, int fps);
    ~Engine();

    SDL_Renderer* R() {return render.Renderer();};  // for testing purpose -> will be deleted

    void Close();

    void LoopBegin();
    void LoopEnd();

    void RenderBegin();
    void RenderEnd();

    // render
    void Draw(DRAW_TYPE draw_type, Color col, int x, int y, int w = 0, int h = 0);
    void Print(std::string text, int x, int y, int size = 64);
    void DrawPhysicsBody(PhysicsBody* body, Color col = COLOR_RED);
    void DrawTexture(Texture* texture, int x, int y);
    void DrawAnimation(Animation* animation, int x, int y);

    // physics
    PhysicsBody* NewPhysicsBody(int x, int y, int w, int h);

    // settings
    void SetClearColor(Color col);

    // media
    Texture* NewTexture(const char* file);
    Animation* NewAnimation(Texture* t, int sz_x, int sz_y, int n_frames, double delay);

    // time
    double GetTime();
    double Delta() {return time.Delta();};


    // particle
    Particle* NewParticle(Texture* texture);

private:
    Render render;
    Time time;
    Physics physics;

    Color clear_color;
    std::vector<Particle*> particles;
};


#endif //ENGINE_ENGINE_H
