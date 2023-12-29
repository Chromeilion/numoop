//
// Created by kiki on 12/24/23.
//

#ifndef RK4_HPP
#define RK4_HPP

#include <ode/method.hpp>

namespace oop::ode{

template <typename T>

class RungeKutta4 : public ODE<T> {

public:

    // Implement Runge-Kutta 4 method for vector case
    arma::Mat<T> method_vec(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {

        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::Col<T> k1 = this->h * this->f_vec(t(i - 1), result_mat.col(i - 1));
            arma::Col<T> k2 = this->h * this->f_vec(t(i - 1) + this->h / 2, result_mat.col(i - 1) + k1 / 2);
            arma::Col<T> k3 = this->h * this->f_vec(t(i - 1) + this->h / 2, result_mat.col(i - 1) + k2 / 2);
            arma::Col<T> k4 = this->h * this->f_vec(t(i - 1) + this->h, result_mat.col(i - 1) + k3);

            result_mat.col(i) = result_mat.col(i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        }
        this->save_vec(result_mat, t, "result_rk4_vector.csv");
        return result_mat;
    }

    // Implementation for scalar case
    arma::Mat<T> method_scalar(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {

        for (arma::uword i = 1; i < t.n_elem; ++i) {
            T k1 = this->h * this->f_scal(t(i - 1), result_mat(0,i - 1));
            T k2 = this->h * this->f_scal(t(i - 1) + this->h / 2, result_mat(0,i - 1) + k1 / 2);
            T k3 = this->h * this->f_scal(t(i - 1) + this->h / 2, result_mat(0,i - 1) + k2 / 2);
            T k4 = this->h * this->f_scal(t(i - 1) + this->h, result_mat(0,i - 1) + k3);

            result_mat(0,i) = result_mat(0,i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        }
        this->save_scalar(result_mat, t, "result_rk4_scalar.csv");
        return result_mat;

    }
};
}
#endif //RK4_HPP