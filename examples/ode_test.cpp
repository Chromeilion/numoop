// Example usage

#include "ode/ode_module.hpp"
int main() {
    auto f = [](double t, const arma::vec& y) -> arma::vec {
        // Example system: dy1/dt = y2, dy2/dt = -y1
        return arma::vec({y(1), -y(0)});
    };

    auto f_scalar = [](double t, double y) -> double {
        // Example scalar ODE: dy/dt = -y
        return t + y;
    };

    double h = 0.05;
    double T = 0.5;

    // For a system with two variables
    arma::vec y0_twovars = {0.0, 1.0};
    euler(f, y0_twovars, h, T);

    // For a scalar ODE
    double y0_scalar = 1.0;
    double x0_scalar = 0.0;
    euler(f_scalar, x0_scalar, y0_scalar, h, T);

    return 0;
}