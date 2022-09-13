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
#include "gui/gui.h"


enum DRAW_TYPE {
    DRAW_RECT,
    DRAW_FILL_RECT,
    DRAW_LINE,
    DRAW_PIXEL,
    DRAW_CIRCLE,
    DRAW_FILL_CIRCLE
};


class Engine {
public:
    // constructor
    Engine(const std::string& wname, const int& w, const int& h, const int& fps);
    ~Engine();
    void Close();


    // loop
    void LoopBegin();
    void LoopEnd();

    void RenderBegin();
    void RenderEnd();


    // render
    void Draw(const DRAW_TYPE& draw_type, const Color& col, const int& x, const int& y, const int& w = 0, const int& h = 0);
    void Print(const std::string& text, const int& x, const int& y, const int& size = 64);
    void DrawTexture(Texture* texture, const int& x, const int& y);
    void DrawAnimation(Animation* animation, const int& x, const int& y);


    // physics
    PhysicsBody* NewPhysicsBody(const int& x, const int& y, const double& rad, const Color& col = COLOR_GREEN);


    // settings
    void SetClearColor(Color col);


    // media
    Texture* NewTexture(const char* file);
    Animation* NewAnimation(Texture* t, const int& sz_x, const int& sz_y, const int& n_frames, const double& delay);


    // time
    double GetTime();
    double Delta();
    const unsigned int& GetFramerate();


    // particle
    Particle* NewParticle(Texture* texture);


    // gui
    Button* ButtonNew(void (*act)(), const std::string& val, const unsigned& ft_size, const int& x, const int& y, const int& w = 0, const int& h = 0);
    void ButtonDelete(Button* bt_to_delete);

    // debug
    void RenderPhysicsBodies();


private:
    MediaManager media_manager;
    Render render;
    Time time;
    Physics physics;
    GUI gui;

    Color clear_color;
    std::vector<Particle*> particles;
};


#endif //ENGINE_ENGINE_H
