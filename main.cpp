#include <cmath>
#include <matplot/matplot.h>
#include <Eigen/Dense>
#include <iostream>

int main() {
    using namespace matplot;

    /* 1. Plot using std::vector, iota and transform */
    std::vector<double> t = iota(0, pi / 50, 10 * pi);
    std::vector<double> st = transform(t, [](auto x) { return sin(x); });
    std::vector<double> ct = transform(t, [](auto x) { return cos(x); });

    auto l_1 = plot3(st, ct, t);
    show();


    /* 2. Plot using Eigen elementwise operations */
    int n_points = 1000;
    Eigen::VectorXf x = Eigen::VectorXf::LinSpaced(n_points, 0, 10 * pi);
    Eigen::VectorXf sx = x.array().sin();
    Eigen::VectorXf cx = x.array().cos();

    auto l_2 = plot3(sx, cx, x);
    show();

    return 0;
}

// #include <SDL.h>
// #include <SDL2_gfx\SDL2_gfxPrimitives.h>
// #include <stdio.h>

// int main(int argc, char* argv[]) {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("SDL2 gfx example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

//     int x = 10;
//     int y = 10;
//     int value = 42;

//     char buffer[256];
//     sprintf(buffer, "Value: %d", value);

//     stringRGBA(renderer, x, y, buffer, 255, 255, 255, 255);

//     SDL_RenderPresent(renderer);

//     SDL_Delay(5000);

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }