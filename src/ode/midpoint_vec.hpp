//
// Created by kiki on 12/29/23.
//

#ifndef MIDPOINT_VEC_HPP
#define MIDPOINT_VEC_HPP

#include <ode/method_vec.hpp>

namespace oop::ode_vec{

template <typename T>

class Midpoint : public ODE_Vec<T> {

public:

    using func_vec = std::function<arma::Col<T>(T, const arma::Col<T>&)>;

    Midpoint(func_vec f = {}, arma::Col<T>& y0 = {}, T& h = {}, T& end = {})
        : ODE_Vec<T>(f, y0, h, end) {}

    // Implement Midpoint method for vector case
    arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {

        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::Col<T> k1 = this->h * this->f(t(i - 1), result_mat.col(i - 1));
            arma::Col<T> k2 = this->h * this->f(t(i - 1) + this->h / 2, result_mat.col(i - 1) + k1 / 2);
            result_mat.col(i) = result_mat.col(i - 1) + k2;
        }
        this->save(result_mat, t, "result_midpoint_vector.csv");
        return result_mat;
    }
};
} // namespace oop::ode_vec

#endif //MIDPOINT_VEC_HPP