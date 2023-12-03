//
// Created by kiki on 12/3/23.
//

#ifndef MIDPOINT_HPP
#define MIDPOINT_HPP

#include <functional>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <string>

// Midpoint method for vector ODEs
void midpoint(const std::function<arma::vec(double, const arma::vec&)>& f, const arma::vec& y0, double h, double T, const std::string& filename = "midpoint_vector_result.csv")

// Midpoint method for scalar ODEs
void midpoint(const std::function<double(double, double)>& f, double y0, double h, double T, const std::string& filename = "midpoint_scalar_result.csv")



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


#endif //MIDPOINT_HPP