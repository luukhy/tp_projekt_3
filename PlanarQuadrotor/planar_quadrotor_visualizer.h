#pragma once

#include <memory>
#include <SDL.h>
#include <matplot/matplot.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>

#include "planar_quadrotor.h"

class PlanarQuadrotorVisualizer {
private:
    PlanarQuadrotor *quadrotor_ptr;
    std::vector<
    bool change_animation = false;
    
public:
    PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr);
    void render_building(std::shared_ptr<SDL_Renderer> &gRenderer, PlanarQuadrotor);
};