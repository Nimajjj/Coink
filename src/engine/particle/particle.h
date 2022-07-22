//
// Created by Ben on 21/07/2022.
//

#ifndef ENGINE_PARTICLE_H
#define ENGINE_PARTICLE_H
#include <stdlib.h>
#include <vector>
#include "SDL.h"
#include "../types.h"

/*
 * TODO :
 *  - color random : gradiant + variation
 *  - acceleration + friction sucks
 *  - loading parameters from .json file
 *  - format code aaaaaaaaaaaaaaaaaargh...
 *
 *
 *  Extremly fun system to code :)
 */

class Particle {
public:
    int particles_count;

    // default
    SDL_Texture* texture;
    int weight, height;
    double emit_delay;
    int emit_occurence;
    double time_elapsed;
    unsigned int max_particles;

    // particles params
    vec2 origin;
    vec2 velocity;
    vec2 acceleration;
    vec2 friction;
    Color color;
    double rotation;
    double max_lifetime;
    double stop_acceleration;

    // params randomness
    vec2 r_size;
    vec2 r_origin;
    vec2 r_velocity;
    vec2 r_acceleration;
    vec2 r_friction;
    double r_rotation;
    double r_stop_acceleration;
    int r_emit_occurence;


    // soa
    std::vector<vec2> sizes;
    std::vector<vec2> positions;
    std::vector<vec2> velocities;
    std::vector<vec2> accelerations;
    std::vector<vec2> frictions;
    std::vector<double> rotations;
    std::vector<double> current_lifetime;
    std::vector<double> stop_accelerations;

    Particle(SDL_Texture* tex);
    ~Particle();

    void Update(SDL_Renderer* render);


    // setter params value
    void SetOrigin(const vec2& param)       {origin = param;} ;
    void SetSize(const vec2& param)         {weight = param.x; height = param.y;} ;
    void SetVelocity(const vec2& param)     {velocity = param;};
    void SetAcceleration(const vec2& param) {acceleration = param;};
    void SetFriction(const vec2& param)     {friction = param;};
    void SetRotation(const double& param)   {rotation = param;};
    void SetLifetime(const double& param)   {max_lifetime = param;};
    void SetMaxParticle(const double& param){max_particles = param;};
    void SetStopAccel(const double& param)  {stop_acceleration = param;};
    void SetEmitDelay(const double& param)   {emit_delay = param;};
    void SetEmitOccurence(const int& param)   {emit_occurence = param;};
    void SetColor(const Color& param)       {
        color = param;
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
    };

    // setter random params value
    void SetRandomOrigin(const vec2& param)         {r_origin = param;} ;
    void SetRandomVelocity(const vec2& param)       {r_velocity = param;};
    void SetRandomAcceleration(const vec2& param)   {r_acceleration = param;};
    void SetRandomFriction(const vec2& param)       {r_friction = param;};
    void SetRandomSize(const vec2& param)           {r_size = param;};
    void SetRandomRotation(const double& param)     {r_rotation = param;};
    void SetRandomStopAccel(const double& param)    {r_stop_acceleration = param;};
    void SetRandomEmitOccurence(const int& param)    {emit_occurence = param;};
};


#endif //ENGINE_PARTICLE_H
