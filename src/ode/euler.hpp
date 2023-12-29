//
// Created by kiki on 12/24/23.
//

#ifndef EULER_HPP
#define EULER_HPP

#include <ode/method.hpp>

namespace oop::ode{

template <typename T>

class Euler : public ODE<T> {

public:

    // Implement Euler method for vector case
    arma::Mat<T> method_vec(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {    
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat.col(i) = result_mat.col(i - 1) + this->h * this->f_vec(t(i), result_mat.col(i - 1));
        }
        this->save_vec(result_mat, t, "result_euler_vector.csv");
        return result_mat;
    }

    // Implementation for scalar case
    arma::Mat<T> method_scalar(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat(0,i) = result_mat(0,i-1) + this->h * this->f_scal(t(i), result_mat(0,i-1));
        }
        this->save_scalar(result_mat, t, "result_euler_scalar.csv");
        return result_mat;
    }
};
}
#endif //EULER_HPP