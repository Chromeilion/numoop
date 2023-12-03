//
// Created by kiki on 12/3/23.
//

#ifndef RUNGR_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include <functional>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <string>

// Runge-Kutta method for vector ODEs
void runge_kutta(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "runge_kutta_vector_result.csv");

// Runge-Kutta method for scalar ODEs
void runge_kutta(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename = "runge_kutta_scalar_result.csv");




// Runge-Kutta method for vector ODEs
void runge_kutta(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "runge_kutta_vector_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with initial conditions
    arma::mat rk_mat(y0.n_elem, steps);

    // Set the initial conditions
    rk_mat.col(0) = y0;

    // Perform Runge-Kutta method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        arma::vec k1 = h * f(t(i - 1), rk_mat.col(i - 1));
        arma::vec k2 = h * f(t(i - 1) + h / 2, rk_mat.col(i - 1) + k1 / 2);
        arma::vec k3 = h * f(t(i - 1) + h / 2, rk_mat.col(i - 1) + k2 / 2);
        arma::vec k4 = h * f(t(i - 1) + h, rk_mat.col(i - 1) + k3);

        rk_mat.col(i) = rk_mat.col(i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }

    // Append the time vector as the first row
    rk_mat.insert_rows(0, t.t());

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    file << "t";
    for (arma::uword i = 0; i < y0.n_elem; ++i) {
        file << ",y" << i + 1;
    }
    file << "\n";
    
    arma::mat mat = rk_mat.t();
    mat.save(file, arma::csv_ascii);

    std::cout << "Result using Runge-Kutta method saved to " << filename << "\n";
}   

// Runge-Kutta method for scalar ODEs
void runge_kutta(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename = "runge_kutta_scalar_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with initial conditions
    arma::mat rk_mat(2, steps);

    // Set the initial conditions
    rk_mat(1, 0) = y0;

    // Perform Runge-Kutta method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        double k1 = h * f(t(i - 1), rk_mat(1, i - 1));
        double k2 = h * f(t(i - 1) + h / 2, rk_mat(1, i - 1) + k1 / 2);
        double k3 = h * f(t(i - 1) + h / 2, rk_mat(1, i - 1) + k2 / 2);
        double k4 = h * f(t(i - 1) + h, rk_mat(1, i - 1) + k3);

        rk_mat(1, i) = rk_mat(1, i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }

    // Append the time vector as the first row
    rk_mat.row(0) = t.t();

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    file << "t,y\n";

    arma::mat mat = rk_mat.t();
    mat.save(file, arma::csv_ascii);

    std::cout << "Result using Runge-Kutta method for scalar ODE saved to " << filename << "\n";
}

#endif //RUNGE_KUTTA_HPP