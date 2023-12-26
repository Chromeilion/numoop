// Example usage

#include <cmath>
#include <chrono>
#include "ode/ode.hpp"

int main() {
    std::cout << "\n";
    std::cout << "Let's solve some ODE's!\n" << std::endl;

    auto f_vector = [](double, const arma::vec& y) -> arma::vec {
        // Example system: dy0/dt = y1, dy1/dt = -y0
        return arma::vec({y(1), -y(0)});
    };
    std::cout << "Example system ODE: dy0/dt = y1, dy1/dt = -y0" << std::endl;

    double h1 = 0.05;
    std::cout << "Step considered: " << h1 << std::endl;

    double T1 = 0.5;
    std::cout << "Final time: " << T1 << std::endl;

    arma::vec y0_twovars = {0.0, 1.0};
    std::cout << "Initial conditions: " << arma::trans(y0_twovars) << std::endl;

    arma::uword steps1 = static_cast<arma::uword>(T1 / h1) + 1;
    arma::vec time1 = arma::linspace(0, T1, steps1);

    auto y1_function = [](double t) -> double {
        return 0.5 * std::exp(-t) * (std::exp(2 * t) - 1);
    };

    auto y2_function = [](double t) -> double {
        return 0.5 * std::exp(-t) * (std::exp(2 * t) + 1);
    };

    arma::mat vector_solution(time1.n_elem, 2);
    for (arma::uword i = 0; i < time1.n_elem; ++i) {
        vector_solution(i, 0) = y1_function(time1(i));
        vector_solution(i, 1) = y2_function(time1(i));
    }


    // Euler method for a system with two variables
    Euler obj1;
    auto start1 = std::chrono::high_resolution_clock::now();
    arma::mat eul1 = obj1.ode(f_vector, y0_twovars, h1, T1);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    std::cout << "Euler system runtime: " << duration1.count() << " microseconds" << std::endl;
    eul1 = eul1.t();
    eul1 -= vector_solution;
    arma::rowvec e1 = eul1.row(steps1 -1);
    e1 = arma::abs(e1);
    std::cout << "Error at time T: " << e1 <<  std::endl;
    std::cout << "\n";

    // Runge-Kutta method for a system with two variables
    Rk4 obj2;
    auto start3 = std::chrono::high_resolution_clock::now();
    arma::mat rk1 = obj2.ode(f_vector, y0_twovars, h1, T1);
    auto end3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);
    std::cout << "Runge-Kutta 4 system runtime: " << duration3.count() << " microseconds" << std::endl;
    rk1 = rk1.t();
    rk1 -= vector_solution;
    arma::rowvec e3 = rk1.row(steps1 - 1);
    e3 = arma::abs(e3);
    std::cout << "Error at time T: " << e3 <<  std::endl;
    std::cout << "\n";

    // Midpoint method for a system with two variables
    Midpoint obj3;
    auto start5 = std::chrono::high_resolution_clock::now();
    arma::mat midp1 = obj3.ode(f_vector, y0_twovars, h1, T1);
    auto end5 = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(end5 - start5);
    std::cout << "Midpoint system runtime: " << duration5.count() << " microseconds" << std::endl;
    midp1 = midp1.t();
    midp1 -= vector_solution;
    arma::rowvec e5 = midp1.row(steps1 -1);
    e5 = arma::abs(e5);
    std::cout << "Error at time T: " << e5 <<  std::endl;

    std::cout << "\n";
    
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
    Euler obj4;
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
    Rk4 obj5;
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
    Midpoint obj6;
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