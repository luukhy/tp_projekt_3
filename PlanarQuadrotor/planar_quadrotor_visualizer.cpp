#include "planar_quadrotor_visualizer.h"


PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * [DONE]          1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * [IN PROGRESS]   2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer, PlanarQuadrotor quadrotor) {
    struct Point {
        float x;
        float y;
    };
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta, alpha;

    /* x, y, theta coordinates */
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];
    alpha = q_theta;

    int fan_dist = 10;   // distance of the fan leg from the tip of the quadrotor
    int r = 60;         // half of the quadrotor width
    int h = 30;         // hight of the fans

    int berx = 20;   // big elipse x radius 
    int bery = 7;    // big elipse y radius 
    int serx = 15;    // small elipse x radious      
    int sery = 5;    // small elipse y radious      

    float delta_x = fan_dist * std::cos(q_theta);       // x coord absolute distance value from the tip of the quadrotor to the fan leg
    float delta_y = fan_dist * std::sin(q_theta);       // y coord absolute distance value from the tip of the quadrotor to the fan leg
    float delta_a = h * std::sin(alpha);                // x coord absolute distance value from the intersection of the fan leg and the quadrotor body
    float delta_b = h * std::cos(alpha);                // y coord absolute distance value from the intersection of the fan leg and the quadrotor body

    Point R_prime         = {q_x - std::cos(q_theta)*r, q_y + std::sin(q_theta)*r};             // left quadrotor tip
    Point R               = {q_x + r*std::cos(q_theta), q_y - std::sin(q_theta)*r};             // right quadrotor tip 
    
    Point P_prime         = {R_prime.x + delta_x, R_prime.y - delta_y};                         // point where the right fan leg and quadrotor meet 
    Point P               = {R.x - delta_x, R.y + delta_y};                                     // point where the left fan leg and quadrotor meet

    Point P_plus_prime    = {P_prime.x - delta_a, P_prime.y - delta_b};
    Point P_plus          = {P.x - delta_a, P.y - delta_b};

    Point S_big;
    Point S_small;
    Point S_prime_big;
    Point S_prime_small;

    if (SDL_GetTicks() - quadrotor_ptr->animation_time > 70)
    {
        this->change_animation = !(this->change_animation);
        quadrotor_ptr->animation_time = SDL_GetTicks();
    }
    if (change_animation) {
        S_big = {P_plus.x + berx, P_plus.y};
        S_small = {P_plus.x - serx, P_plus.y};
        S_prime_big = {P_plus_prime.x - berx, P_plus_prime.y};
        S_prime_small = {P_plus_prime.x + serx, P_plus_prime.y};
    }
    else 
    {
        S_big = {P_plus.x - berx, P_plus.y};
        S_small = {P_plus.x + serx, P_plus.y};
        S_prime_big = {P_plus_prime.x + berx, P_plus_prime.y};
        S_prime_small = {P_plus_prime.x - serx, P_plus_prime.y};
    }


    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(gRenderer.get(), q_x, q_y, 0, 0);
    // QUADROTOR
    thickLineColor(gRenderer.get(), R_prime.x, R_prime.y, R.x, R.y, 15,  0xFF979797);
    // FAN LEGS
    thickLineColor(gRenderer.get(), P_prime.x, P_prime.y, P_plus_prime.x, P_plus_prime.y, 5, 0xFF000000);
    thickLineColor(gRenderer.get(), P.x, P.y, P_plus.x, P_plus.y, 5, 0xFF000000);
    // FANS
    filledEllipseColor(gRenderer.get(), S_big.x, S_big.y, berx, bery, 0xFFFF0000);
    filledEllipseColor(gRenderer.get(), S_small.x, S_small.y, serx, sery, 0xFFFF0000);
    filledEllipseColor(gRenderer.get(), S_prime_big.x, S_prime_big.y, berx, bery, 0xFFFF0000);
    filledEllipseColor(gRenderer.get(), S_prime_small.x, S_prime_small.y, serx, sery, 0xFFFF0000);

    gfxPrimitivesSetFont(NULL, NULL, NULL);
    stringColor(gRenderer.get(), 0, 0, "chuj", 0xFF000000);
}
// q_x - (std::sin(q_theta)*r)/2
// q_y + (std::cos(q_theta)*r)/2
// q_x + (std::sin(q_theta)*r)/2
// q_y - (std::cos(q_theta)*r)/2
