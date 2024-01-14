//
// Created by kiki on 12/29/23.
//

#ifndef METHOD_VEC_HPP
#define METHOD_VEC_HPP

#include <armadillo>

namespace oop::ode_vec{

template <typename T>

class ODE_Vec {

public:

    // Typedef for the function type
    using func_vec = std::function<arma::Col<T>(T, const arma::Col<T>&)>;

    // Default constructor and destructor
    ODE_Vec(const func_vec f_ = {}, const arma::Col<T> y0_= {}, const T h_= {}, const T end_= {}): 
            f(f_), y0(y0_), h(h_), end(end_) {}

    virtual ~ODE_Vec() = default;

    // Virtual method for vector case
    virtual arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) = 0;
 
    // Set the vector function
    void set_func(const func_vec& new_func) {
        f = new_func;
    }
    // Set the vector starting point
    void set_y0(const arma::Col<T>& new_y0) {
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

    // Method for vector case
    arma::Mat<T> ode() {

        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::Col<T> t = arma::linspace(0, end, steps);
        arma::Mat<T> result_mat = instantiate(steps);
        result_mat = method(result_mat, t);
        arma::Mat<T> out = result_mat.t();
        return out;
    }

protected:

    func_vec f;      // Member variable for the vector function
    arma::Col<T> y0; // Member variable for the vector starting point
    T h;             // Member variable for the jump used
    T end;           // Member variable for the final time

    // Instansiating the matrix in the vector case
    arma::Mat<T> instantiate(arma::uword steps) {
        arma::Mat<T> result_mat(y0.n_elem, steps);
        result_mat.col(0) = y0;
        return result_mat;
    }
    
    // Save function for vector case
    void save(arma::Mat<T> result_mat, const arma::Col<T> t, 
                  const std::string& filename) {
        // Append the time vector
        result_mat.insert_rows(0, t.t());

        std::ofstream file(filename);
        if (file.is_open()) {
            file << "t,y0";
            for (arma::uword i = 1; i < y0.n_elem; ++i) {
                file << ",y" << i;
            }
            file << "\n";
            arma::Mat<T> mat = result_mat.t();
            mat.save(file, arma::csv_ascii);
            std::cout << "Result saved to " << filename << "\n";
        } else {
            std::cerr << "Error: Unable to open file for writing.\n";
        }
    }
};
} // namespace oop::ode_vec

#endif //METHOD_VEC_HPP