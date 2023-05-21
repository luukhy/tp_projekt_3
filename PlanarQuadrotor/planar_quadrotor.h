#pragma once

#include <Eigen/Dense>
#include <tuple>
#include<SDL.h>
#include <matplot/matplot.h>


#include "lqr.h"

class PlanarQuadrotor {
private:
    Eigen::VectorXf z = Eigen::VectorXf::Zero(6);
    Eigen::VectorXf z_dot = Eigen::VectorXf::Zero(6);
    Eigen::VectorXf z_goal = Eigen::VectorXf::Zero(6);
    // m, I, r, g parameters
    Eigen::VectorXf params = Eigen::Vector4f(0.486, 0.00383, 0.25, 9.81); 
    Eigen::Vector2f input = Eigen::Vector2f::Zero();
    int time = SDL_GetTicks();
    int seconds = 0;
    bool show_coords = true;
    std::vector<float> x_history;
    std::vector<float> y_history;
    std::vector<float> theta_history;

public:
    int animation_time = SDL_GetTicks();
    PlanarQuadrotor();
    PlanarQuadrotor(Eigen::VectorXf z);
    void SetGoal(Eigen::VectorXf z_goal);
    Eigen::VectorXf GetState();
    Eigen::VectorXf GetControlState();
    Eigen::Vector2f GravityCompInput();
    std::tuple<Eigen::MatrixXf, Eigen::MatrixXf> Linearize();
    void SetInput(Eigen::Vector2f input);
    void DoCalcTimeDerivatives(); // Shamelessly copied from Drake API
    void DoUpdateState(float dt);
    Eigen::VectorXf Update(Eigen::Vector2f &input, float dt);
    Eigen::VectorXf Update(float dt);
    void ShowHistory();
    void UpdateHistory();
    void ReturnTime();
};
