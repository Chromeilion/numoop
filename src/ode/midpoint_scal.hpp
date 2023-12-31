//
// Created by kiki on 12/29/23.
//

#ifndef MIDPOINT_SCAL_HPP
#define MIDPOINT_SCAL_HPP

#include <ode/method_scal.hpp>

namespace oop::ode_scal{

template <typename T>

class Midpoint_Scal : public ODE_Scal<T> {

public:

    using func_scal = std::function<T(T,T)>;

    Midpoint_Scal(func_scal f = {}, T y0 = {}, T h = {}, T end = {})
        : ODE_Scal<T>(f, y0, h, end) {}

    // Implementation for scalar case
    arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {
        
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            T k1 = this->h * this->f(t(i - 1), result_mat(0,i - 1));
            T k2 = this->h * this->f(t(i - 1) + this->h / 2, result_mat(0,i - 1) + k1 / 2);
            result_mat(0,i) = result_mat(0,i - 1) + k2;
        }
        this->save(result_mat, t, "result_midpoint_scalar.csv");
        return result_mat;
    }
};
} // namespace oop::ode_scal

#endif //MIDPOINT_SCAL_HPP