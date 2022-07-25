//
// Created by Ben on 21/07/2022.
//

#include <iostream>
#include "particle.h"

static void update_vec(std::vector<vec2>& to_update, const vec2& base, const vec2& random) {
    to_update.push_back( base );
    if ( random.x != 0 ) {
        to_update.back().x += rand() % 2 ? static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / random.x ) ) : static_cast<float>( rand() ) / -( static_cast<float>( RAND_MAX / random.x ) ) ;
    }
    if ( random.y != 0 ) {
        to_update.back().y += rand() % 2 ? static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / random.y ) ) : static_cast<float>( rand() ) / -( static_cast<float>( RAND_MAX / random.y ) ) ;
    }
}

static void update_double(std::vector<double>& to_update, const double& base, const double& random) {
    to_update.push_back( base );
    if ( random != 0 ) {
        to_update.back() += rand() % 2 ? static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / random ) ) : static_cast<float>( rand() ) / -( static_cast<float>( RAND_MAX / random ) ) ;
    }
}


Particle::Particle(SDL_Texture* tex) :
        texture(tex),
        origin(vec2()),
        velocity(vec2()),
        acceleration(vec2()),
        friction(vec2()),
        color(Color(0xFF, 0xFF, 0xFF)),
        rotation(0),
        max_lifetime(1000),
        max_particles(100),
        emit_delay(100),
        time_elapsed(0),
        particles_count(0),
        stop_acceleration(0),
        emit_occurence(1),
        r_origin(vec2()),
        r_velocity(vec2()),
        r_acceleration(vec2()),
        r_friction(0),
        r_rotation(0),
        r_size(0),
        r_stop_acceleration(0),
        r_emit_occurence(0)
{
    SDL_SetTextureColorMod( texture, color.r, color.g, color.b );
    SDL_SetTextureAlphaMod( texture, color.a );
    SDL_QueryTexture( texture, NULL, NULL, &weight, &height );
}


Particle::~Particle() {
    SDL_DestroyTexture( texture );
}


void Particle::Update(SDL_Renderer* render) {
    /*
    SDL_SetRenderDrawColor(render, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawLine(render, origin.x - 16, origin.y, origin.x + 16, origin.y);
    SDL_RenderDrawLine(render, origin.x, origin.y - 16, origin.x, origin.y + 16);
    */

    if ( SDL_GetTicks() - time_elapsed > emit_delay && positions.size() < max_particles ) {
        time_elapsed = SDL_GetTicks();

        for ( unsigned i=0; i < (r_emit_occurence != 0 ? emit_occurence + (rand() % r_emit_occurence) : emit_occurence); i++ ) {
            if ( positions.size() >= max_particles ) {
                break;
            }

            sizes.push_back( vec2(weight, height) );
            if ( r_size.x != 0 && r_size.y != 0 ) {
                auto r = rand()%2 ? static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / r_size.x ) ) : static_cast<float>( rand() ) / -( static_cast<float>( RAND_MAX / r_size.x) ) ;

                sizes.back().x += r;
                sizes.back().y += r;
            }

            update_vec( positions, origin, r_origin );
            update_vec( velocities, velocity, r_velocity );
            update_vec( accelerations, acceleration, r_acceleration );
            update_vec( frictions, friction, r_friction );
            update_double( rotations, rotation, r_rotation );
            update_double( stop_accelerations, stop_acceleration, r_stop_acceleration );
            current_lifetime.push_back( 0 );

            particles_count++;
        }
    }


    for (unsigned i=0; i < positions.size(); i++) {
        // erase particle
        current_lifetime[i]++;
        if ( current_lifetime[i] > max_lifetime ) {
            sizes.erase( sizes.begin() );
            positions.erase( positions.begin() );
            velocities.erase( velocities.begin() );
            accelerations.erase( accelerations.begin() );
            frictions.erase( frictions.begin() );
            rotations.erase( rotations.begin() );
            current_lifetime.erase( current_lifetime.begin() );

            particles_count--;
            continue;
        }

        // update particle
        if ( sizes[i].x == 0.0 && sizes[i].y == 0.0 ){
            sizes[i] = { (double)weight, (double)height };
        }

        if ( current_lifetime[i] > stop_accelerations[i] && stop_accelerations[i] != 0 ) {
            velocities[i] -= frictions[i];
        } else {
            velocities[i] += accelerations[i];
        }

        positions[i] += velocities[i];
        rotations[i] += rotation;


        // draw particle
        SDL_Rect dstrect = { (int)positions[i].x, (int)positions[i].y, (int)sizes[i].x, (int)sizes[i].y };
        SDL_RenderCopyEx(
                render,
                texture,
                NULL,
                &dstrect,
                rotations[i],
                NULL,
                SDL_FLIP_NONE
                );
    }
}


