//
// Created by kiki on 12/29/23.
//

#ifndef RK4_VEC_HPP
#define RK4_VEC_HPP

#include <ode/method_vec.hpp>

namespace oop::ode_vec{

template <typename T>

class RK4 : public ODE_Vec<T> {

public:

    using func_vec = std::function<arma::Col<T>(T, const arma::Col<T>&)>;

    RK4(func_vec f = {}, arma::Col<T>& y0 = {}, T& h = {}, T& end = {})
        : ODE_Vec<T>(f, y0, h, end) {}

    // Implement Runge-Kutta 4 method for vector case
    arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {

        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::Col<T> k1 = this->h * this->f(t(i - 1), result_mat.col(i - 1));
            arma::Col<T> k2 = this->h * this->f(t(i - 1) + this->h / 2, result_mat.col(i - 1) + k1 / 2);
            arma::Col<T> k3 = this->h * this->f(t(i - 1) + this->h / 2, result_mat.col(i - 1) + k2 / 2);
            arma::Col<T> k4 = this->h * this->f(t(i - 1) + this->h, result_mat.col(i - 1) + k3);

            result_mat.col(i) = result_mat.col(i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        }
        this->save(result_mat, t, "result_rk4_vector.csv");
        return result_mat;
    }
};
} // namespace oop::ode_vec

#endif //RK4_VEC_HPP