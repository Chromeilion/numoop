//
// Created by kiki on 12/24/23.
//

#ifndef MIDPOINT_HPP
#define MIDPOINT_HPP

#include <ode/method.hpp>

namespace oop::ode{

template <typename T>

class Midpoint : public ODE<T> {

public:

    // Implement Midpoint method for vector case
    arma::Mat<T> method_vec(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::Col<T> k1 = this->h * this->f_vec(t(i - 1), result_mat.col(i - 1));
            arma::Col<T> k2 = this->h * this->f_vec(t(i - 1) + this->h / 2, result_mat.col(i - 1) + k1 / 2);

            result_mat.col(i) = result_mat.col(i - 1) + k2;
        }
        this->save_vec(result_mat, t, "result_midpoint_vector.csv");
        return result_mat;
    }

    // Implementation for scalar case
    arma::Mat<T> method_scalar(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            T k1 = this->h * this->f_scal(t(i - 1), result_mat(0,i - 1));
            T k2 = this->h * this->f_scal(t(i - 1) + this->h / 2, result_mat(0,i - 1) + k1 / 2);

            result_mat(0,i) = result_mat(0,i - 1) + k2;
        }
        this->save_scalar(result_mat, t, "result_midpoint_scalar.csv");
        return result_mat;
    }
};
}
#endif //MIDPOINT_HPP