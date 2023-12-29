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
    using func_scalar = std::function<double(double, double)>;
    using func_vec = std::function<arma::vec(double, const arma::vec&)>;

    // Virtual method for vector case
    virtual arma::mat method_vec(arma::mat& result_mat, const arma::vec& t) = 0;
 
    // Virtual method for scalar case
    virtual arma::mat method_scalar(arma::mat& result_mat, const arma::vec& t) = 0;

    // Set the scalar function f
    void set_fun_scal(const func_scalar& new_func) {
        f_scal = new_func;
    }
    // Set the vector function
    void set_fun_vec(const func_vec& new_func) {
        f_vec = new_func;
    }
    // Set the scalar starting point
    void set_y0_scal(double new_y0) {
        y0_scal = new_y0;
    }
    // Set the vector starting point
    void set_y0_vec(const arma::vec& new_y0) {
        y0_vec = new_y0;
    } 
    // Set the step used for the ODE
    void set_h(double new_h) {
        h = new_h;
    }   
    // Set the final time for the ODE
    void set_end(double new_end) {
        end = new_end;
    }                                

    // Method for scalar case
    arma::mat ode_scal() {

        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::vec t = arma::linspace(0, end, steps);
        arma::mat result_mat = instantiate_scalar(steps);
        result_mat = method_scalar(result_mat, t);
        arma::mat out = result_mat.t();
        return out;
    }

    // Method for vector case
    arma::mat ode_vec() {

        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::vec t = arma::linspace(0, end, steps);
        arma::mat result_mat = instantiate_vec(steps);
        result_mat = method_vec(result_mat, t);
        arma::mat out = result_mat.t();
        return out;
    }


protected:

    func_scalar f_scal; // Member variable for the scalar function
    func_vec f_vec;     // Member variable for the vector function
    double y0_scal;     // Member variable for the scalar starting point
    arma::vec y0_vec;   // Member variable for the scalar starting point
    double h;           // Member variable for the jump used
    double end;         // Member variable for the final time
//const arma::Col<T>& y0,

    // Instansiating the matrix in the vector case
    arma::mat instantiate_vec(arma::uword steps) {
        arma::mat result_mat(y0_vec.n_elem, steps);
        result_mat.col(0) = y0_vec;
        return result_mat;
    }

    // Instansiating the matrix in the scalar case
    arma::mat instantiate_scalar(arma::uword steps) {
        arma::mat result_mat(1,steps);
        result_mat(0,0) = y0_scal;
        return result_mat;
    }
    
    // Save function for vector case
    void save_vec(arma::mat result_mat, const arma::vec t, 
                  const std::string& filename) {
        // Append the time vector
        result_mat.insert_rows(0, t.t());

        std::ofstream file(filename);
        if (file.is_open()) {
            file << "t,y0";
            for (arma::uword i = 1; i < y0_vec.n_elem; ++i) {
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
    void save_scalar(arma::mat result_mat, const arma::vec t, 
                     const std::string& filename) {
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