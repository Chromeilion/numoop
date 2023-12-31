//
// Created by kiki on 12/29/23.
//

#ifndef EULER_VEC_HPP
#define EULER_VEC_HPP

#include <ode/method_vec.hpp>

namespace oop::ode_vec {

template <typename T>

class Euler : public ODE_Vec<T> {

public:

    using func_vec = std::function<arma::Col<T>(T, const arma::Col<T>&)>;

    Euler(func_vec f = {}, arma::Col<T>& y0 = {}, T& h = {}, T& end = {})
        : ODE_Vec<T>(f, y0, h, end) {}

    // Implement Euler method for vector case
    arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat.col(i) = result_mat.col(i - 1) + this->h * this->f(t(i), result_mat.col(i - 1));
        }
        this->save(result_mat, t, "result_euler_vector.csv");
        return result_mat;
    }
};
} // namespace oop::ode_vec

#endif // EULER_VEC_HPP