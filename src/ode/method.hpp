//
// Created by kiki on 12/24/23.
//

#ifndef METHOD_HPP
#define METHOD_HPP

#include <armadillo>
#include <functional>
#include <iostream>
#include <variant>
#include <fstream>
#include <vector>
#include <type_traits>

class ODE {
public:
    virtual ~ODE() = default;

    // Typedef for the function types
    using func_scalar = std::function<arma::vec(double, double)>;
    using func_vec = std::function<arma::vec(double, const arma::vec&)>;

    // Explicit constructor for scalar functions
    //explicit ODE(const func_scalar& scalar_func) : f_scal(scalar_func) {}

    // Explicit constructor for vector functions
    //explicit ODE(const func_vec& vector_func) : f_vec(vector_func) {}

    // Set the scalar function f
    void set_scal_fun(const func_scalar& new_func) {
        f_scal = new_func;
    }
    // Set the vector function
    void set_vec_fun(const func_vec& new_func) {
        f_vec = new_func;
    }

    // Virtual method for vector case
    virtual arma::mat method_vec(arma::mat& result_mat, const arma::vec& y0, 
                                  const arma::vec& t, double h) const = 0;

    // Virtual method for scalar case
    virtual arma::mat method_scalar(arma::mat& result_mat, const arma::vec& t, 
                                    double h) const = 0;

    // Method for scalar case
    arma::mat ode(double y0, double h, double end) {

        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::vec t = arma::linspace(0, end, steps);

        arma::mat result_mat = instantiate_scalar(y0, steps);

        result_mat = method_scalar(result_mat, t, h);

        arma::mat out = result_mat.t();
        return out;
    }

    // Method for vector case
    arma::mat ode(const arma::vec& y0, double h, double end) {

        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::vec t = arma::linspace(0, end, steps);

        arma::mat result_mat = instantiate_vec(y0, steps);

        result_mat = method_vec(result_mat, y0, t, h);

        arma::mat out = result_mat.t();
        return out;
    }

protected:
    func_scalar f_scal; // Member variable for the scalar function
    func_vec f_vec;    // Member variable for the vector function
    
    // Instansiating the matrix in vector case
    arma::mat instantiate_vec(const arma::vec& y0, arma::uword steps) {
        arma::mat result_mat(y0.n_elem, steps);
        result_mat.col(0) = y0;
        return result_mat;
    }
    // Instansiating the matrix in scalar case
    arma::mat instantiate_scalar(double y0, arma::uword steps) {
        arma::mat result_mat(1, steps);
        result_mat(0,0) = y0;
        return result_mat;
    }
    
    // Save function for vector case
    void save_vec(arma::mat result_mat, const arma::vec t, 
              const arma::vec& y0, const std::string& filename) {
        // Append the time vector
        result_mat.insert_rows(0, t.t());

        std::ofstream file(filename);
        if (file.is_open()) {
            file << "t,y0";
            for (arma::uword i = 1; i < y0.n_elem; ++i) {
                file << ",y" << i;
            }
            file << "\n";
            arma::mat mat = result_mat.t();
            mat.save(file, arma::csv_ascii);
            std::cout << "Result saved to " << filename << "\n";
        } else {
            std::cerr << "Error: Unable to open file for writing.\n";
        }
    }

    // Save function for scalar case
    void save_scalar(arma::mat result_mat, const arma::vec t, const std::string& filename) {
        // Append the time vector
        result_mat.insert_rows(0, t.t());

       std::ofstream file(filename);
        if (file.is_open()) {
            file << "t,y\n";
            arma::mat mat = result_mat.t();
            mat.save(file, arma::csv_ascii);
            std::cout << "Result saved to " << filename << "\n";
        } else {
            std::cerr << "Error: Unable to open file for writing.\n";
        }
    }
};
#endif //METHOD_HPP