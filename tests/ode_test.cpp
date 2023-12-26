// Example usage

#include <cmath>
#include <chrono>
#include "ode/ode.hpp"

int main() {
    std::cout << "\n";
    std::cout << "Let's solve some ODE's!\n" << std::endl;

     auto f_scalar = [](double t, double y) -> double {
        // Example scalar ODE: dy/dt = y + t
        return t + y;
    };
    std::cout << "Example scalar ODE: dy/dt = y + t" << std::endl;

    double h2 = 0.05;
    std::cout << "Step considered: " << h2 << std::endl;

    double T2 = 0.5;
    std::cout << "Final time: " << T2 << std::endl;

        double y0_scalar = 1.0;
    std::cout << "Initial conditions: " << y0_scalar << std::endl;

    std::cout << "\n";

    arma::uword steps2 = static_cast<arma::uword>(T2 / h2) + 1;
    arma::vec time2 = arma::linspace(0, T2, steps2);

    auto scalar_solution = [](double t) -> double {
        return -t + 2 * std::exp(t) - 1;
    };
    arma::vec scalar_solution_values = arma::vec(time2.n_elem);
    for (arma::uword i = 0; i < time2.n_elem; ++i) {
        scalar_solution_values(i) = scalar_solution(time2(i));
    }

    // Euler method for a scalar ODE
    euler::Euler obj4;
    auto start2 = std::chrono::high_resolution_clock::now();
    arma::mat eul2 = obj4.ode(f_scalar, y0_scalar, h2, T2);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "Euler scalar runtime: " << duration2.count() << " microseconds" << std::endl;
    eul2 -= scalar_solution_values;
    double e2 = std::abs(eul2.at(steps2-1,0));
    std::cout << "Error at time T: " << e2 <<  std::endl;
    std::cout << "\n";


    // Runge-Kutta method for a scalar ODE
    rk4::RungeKutta4 obj5;
    auto start4 = std::chrono::high_resolution_clock::now();
    arma::mat rk2 = obj5.ode(f_scalar, y0_scalar, h2, T2);
    auto end4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4);
    std::cout << "Runge-Kutta 4 scalar runtime: " << duration4.count() << " microseconds" << std::endl;
    rk2 -= scalar_solution_values;
    double e4 = std::abs(rk2.at(steps2-1,0));
    std::cout << "Error at time T: " << e4 <<  std::endl;
    std::cout << "\n";
    

    // Midpoint method for a scalar ODE
    midpoint::Midpoint obj6;
    auto start6 = std::chrono::high_resolution_clock::now();
    arma::mat midp2 = obj6.ode(f_scalar, y0_scalar, h2, T2);
    auto end6 = std::chrono::high_resolution_clock::now();
    auto duration6 = std::chrono::duration_cast<std::chrono::microseconds>(end6 - start6);
    std::cout << "Midpoint scalar runtime: " << duration6.count() << " microseconds" << std::endl;
    midp2 -= scalar_solution_values;
    double e6 = std::abs(midp2.at(steps2-1,0));
    std::cout << "Error at time T: " << e6 <<  std::endl;

    std::cout << "\n";
    return 0;
}