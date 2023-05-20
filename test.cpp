#include <cmath>
#include <matplot/matplot.h>
#include <Eigen/Dense>
#include <iostream>
#include <vector>

int main() 
{
    Eigen::VectorXf x = Eigen::VectorXf::LinSpaced(10, 0, 10* matplot::pi);
    Eigen::VectorXf sin = Eigen::VectorXf::LinSpaced(10, 0, 10* matplot::pi);
    auto l = matplot::plot(x, sin);
    matplot::show();
    return 0;
}