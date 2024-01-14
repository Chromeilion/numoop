//
// Created by kiki on 12/29/23.
//

#ifndef METHOD_SCAL_HPP
#define METHOD_SCAL_HPP

#include <armadillo>
#include <functional>
#include <vector>

namespace oop::ode_scal{

template <typename T>

class ODE_Scal {

public:

    // Typedef for the function types
    using func_scal = std::function<T(T,T)>;

    // Default constructor and destructor
    ODE_Scal(const func_scal f_ = {}, const T y0_ = {}, const T h_ = {}, const T end_ = {}): 
              f(f_), y0(y0_), h(h_), end(end_) {}

    virtual ~ODE_Scal() = default;
 
    // Virtual method for scalar case
    virtual arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) = 0;

    // Set the scalar function f
    void set_func(const func_scal& new_func) {
        f = new_func;
    }
    // Set the scalar starting point
    void set_y0(T new_y0) {
        y0 = new_y0;
    }
    // Set the step used for the ODE
    void set_h(T new_h) {
        h = new_h;
    }   
    // Set the final time for the ODE
    void set_end(T new_end) {
        end = new_end;
    }                                

    // Method for scalar case
    arma::Mat<T> ode() {

        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::Col<T> t = arma::linspace(0, end, steps);
        arma::Mat<T> result_mat = instantiate(steps);
        result_mat = method(result_mat, t);
        arma::Mat<T> out = result_mat.t();
        return out;
    }

protected:

    func_scal f; // Member variable for the scalar function
    T y0;          // Member variable for the scalar starting point
    T h;           // Member variable for the jump used
    T end;         // Member variable for the final time

    // Instansiating the matrix in the scalar case
    arma::Mat<T> instantiate(arma::uword steps) {
        arma::Mat<T> result_mat(1,steps);
        result_mat(0,0) = y0;
        return result_mat;
    }
 
    // Save function for scalar case
    void save(arma::Mat<T> result_mat, const arma::Col<T> t, 
                     const std::string& filename) {
        // Append the time vector
        result_mat.insert_rows(0, t.t());

       std::ofstream file(filename);
        if (file.is_open()) {
            file << "t,y\n";
            arma::Mat<T> mat = result_mat.t();
            mat.save(file, arma::csv_ascii);
            std::cout << "Result saved to " << filename << "\n";
        } else {
            std::cerr << "Error: Unable to open file for writing.\n";
        }
    }
};
} // namespace oop::ode_scal

#endif //METHOD_SCAL_HPP