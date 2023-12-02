//
// Created by kiki on 12/1/23.
//

#ifndef ODE_MODULE_HPP
#define ODE_MODULE_HPP

#include <iostream>
#include <fstream>
#include <functional>
#include <armadillo>

// Euler method for vector ODEs
void euler(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "euler_vector_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    arma::mat euler_mat(y0.n_elem, steps);

    // Initialize the matrix with initial conditions
    euler_mat.col(0) = y0;

    // Perform Euler's method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        euler_mat.col(i) = euler_mat.col(i - 1) + h * f(t(i), euler_mat.col(i - 1));
    }

    // Append the time vector as the first row
    euler_mat.insert_rows(0, t.t());

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    file << "t,y0";
    for (arma::uword i = 1; i <= y0.n_elem; ++i) {
        file << ",y" << i;
    }
    file << "\n";
    arma::mat mat = euler_mat.t();
    mat.save(file, arma::csv_ascii);

    std::cout << "Result using Euler method saved to " << filename << "\n";
}

// Euler method for scalar ODEs
void euler(const std::function<arma::vec(double, const arma::vec&)>& f, double x0, double y0, double h, double T, const std::string& filename = "euler_scalar_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with dimensions (2, steps)
    arma::mat euler_mat(2, steps);

    // Set the initial conditions
    euler_mat.col(0) = arma::vec({x0, y0});

    // Perform Euler's method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        euler_mat.col(i) = euler_mat.col(i - 1) + h * f(t(i), euler_mat.col(i - 1));
    }

    // Append the time vector as the first row
    euler_mat.insert_rows(0, t.t());

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    file << "t,x,y\n";

    arma::mat mat = euler_mat.t();
    mat.save(file, arma::csv_ascii);

    std::cout << "Result using Euler method saved to " << filename << "\n";
}


// Runge-Kutta method for vector ODEs
void rk4(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "rk_vector_result.csv") {
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
void rungeKutta(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename = "rk_scalar_result.csv") {
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

// Midpoint method for vector ODEs
void midpoint(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "midpoint_vector_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with initial conditions
    arma::mat midpoint_mat(y0.n_elem, steps);

    // Set the initial conditions
    midpoint_mat.col(0) = y0;

    // Perform Midpoint method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        arma::vec k1 = h * f(t(i - 1), midpoint_mat.col(i - 1));
        arma::vec k2 = h * f(t(i - 1) + h / 2, midpoint_mat.col(i - 1) + k1 / 2);

        midpoint_mat.col(i) = midpoint_mat.col(i - 1) + k2;
    }

    // Append the time vector as the first row
    midpoint_mat.insert_rows(0, t.t());

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    file << "t";
    for (arma::uword i = 0; i < y0.n_elem; ++i) {
        file << ",y" << i + 1;
    }
    file << "\n";

    arma::mat mat = midpoint_mat.t();
    mat.save(file, arma::csv_ascii);

    std::cout << "Result using Midpoint method saved to " << filename << "\n";
}

// Midpoint method for scalar ODEs
void midpoint(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename = "midpoint_scalar_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with initial conditions
    arma::mat midpoint_mat(2, steps);

    // Set the initial conditions
    midpoint_mat(1, 0) = y0;

    // Perform Midpoint method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        double k1 = h * f(t(i - 1), midpoint_mat(1, i - 1));
        double k2 = h * f(t(i - 1) + h / 2, midpoint_mat(1, i - 1) + k1 / 2);

        midpoint_mat(1, i) = midpoint_mat(1, i - 1) + k2;
    }

    // Append the time vector as the first row
    midpoint_mat.row(0) = t.t();

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    file << "t,y\n";

    arma::mat mat = midpoint_mat.t();
    mat.save(file, arma::csv_ascii);

    std::cout << "Result using Midpoint method for scalar ODE saved to " << filename << "\n";
}

#endif //ODE_MODULE_HPP