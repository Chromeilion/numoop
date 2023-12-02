// Example usage

#include "ode/ode_module.hpp"
int main() {
    auto f = [](double t, const arma::vec& y) -> arma::vec {
        // Example system: dy1/dt = y2, dy2/dt = -y1
        return arma::vec({y(1), -y(0)});
    };

    auto f_scalar = [](double t, double y) -> double {
        // Example scalar ODE: dy/dt = -y
        return -y;
    };

    double h = 0.1;
    double T = 2.0;

    // For a system with two variables
    arma::vec y0_twovars = {1.0, 0.0};
    midpoint(f, y0_twovars, h, T);

    // For a scalar ODE
    double y0_scalar = 1.0;
    midpoint(f_scalar, y0_scalar, h, T);

    return 0;
}