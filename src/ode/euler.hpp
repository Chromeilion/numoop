//
// Created by kiki on 12/3/23.
//

#ifndef EULER_HPP
#define EULER_HPP

#include <functional>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <string>

// Euler method for vector ODEs
void euler(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename);

// Euler method for scalar ODEs
void euler(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename);



// Euler method for vector ODEs
void euler(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "euler_vector_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with dimensions (y0.n_elem, steps) and fill with zeros
    arma::mat euler_mat(y0.n_elem, steps);

    // Set the initial conditions
    euler_mat.col(0) = y0;

    // Perform Euler's method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        euler_mat.col(i) = euler_mat.col(i - 1) + h * f(t(i), euler_mat.col(i - 1));
    }

    // Append the time vector as the first row
    euler_mat.insert_rows(0, t.t());

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "t,y0";
        for (arma::uword i = 1; i < y0.n_elem; ++i) {
            file << ",y" << i;
        }
        file << "\n";
        arma::mat mat = euler_mat.t();
        mat.save(file, arma::csv_ascii);
        std::cout << "Result using Euler method for scalar ODE saved to " << filename << "\n";
    } else {
        std::cerr << "Error: Unable to open file for writing.\n";
    }
}

// Euler method for scalar ODEs
void euler(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename = "euler_scalar_result.csv") {
    // Create the vector t containing the jumps
    arma::uword steps = static_cast<arma::uword>(T / h) + 1;
    arma::vec t = arma::linspace(0, T, steps);

    // Initialize the matrix with dimensions (2, steps) and fill with zeros
    arma::mat euler_mat(steps,1);

    // Set the initial conditions
    euler_mat(0,0) = y0;

    // Perform Euler's method
    for (arma::uword i = 1; i < t.n_elem; ++i) {
        euler_mat(i,0) = euler_mat(i - 1,0) + h * f(t(i-1), euler_mat(i - 1,0));
    }

    // Append the time vector as the first column
    euler_mat.insert_cols(0, t);

    // Save the result to the specified or default CSV file with a header
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "t,y\n";
        euler_mat.save(file, arma::csv_ascii);
        std::cout << "Result using Euler method saved to " << filename << "\n";
    } else {
        std::cerr << "Error: Unable to open file for writing.\n";
    }
}

#endif //EULER_HPP