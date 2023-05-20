#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * [DONE]          1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * [IN PROGRESS]   2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer, PlanarQuadrotor quadrotor) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];
    int r = 40;

    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(gRenderer.get(), q_x, q_y, 0, 0);
    filledCircleColor(gRenderer.get(), q_x, q_y, 20, 0x8800FF00);
    lineColor(gRenderer.get(), q_x + r*std::cos(q_theta), q_y - (std::sin(q_theta)*r), q_x - std::cos(q_theta)*r, q_y + std::sin(q_theta)*r, 0xFFFF0000);
    
    //////////////////
    gfxPrimitivesSetFont(NULL, NULL, NULL);
    stringColor(gRenderer.get(), 0, 0, "chuj", 0xFF000000);
}
// q_x - (std::sin(q_theta)*r)/2
// q_y + (std::cos(q_theta)*r)/2
// q_x + (std::sin(q_theta)*r)/2
// q_y - (std::cos(q_theta)*r)/2
