//
// Created by kiki on 12/29/23.
//

#ifndef EULER_SCAL_HPP
#define EULER_SCAL_HPP

#include <ode/method_scal.hpp>
#include <vector>

namespace oop::ode_scal{

template <typename T = double>

class Euler_Scal : public ODE_Scal<T> {

public:

    using func_scal = std::function<T(T,T)>;

    Euler_Scal(func_scal f = {}, T y0 = {}, T h = {}, T end = {})
        : ODE_Scal<T>(f, y0, h, end) {}

    // Implement Euler method for vector case
    arma::Mat<T> method(arma::Mat<T>& result_mat, const arma::Col<T>& t) override {    
        
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat(0,i) = result_mat(0,i - 1) + this->h * this->f(t(i), result_mat(0,i - 1));
        }
        this->save(result_mat, t, "result_euler_scalar.csv");
        return result_mat;
    }
};
} // namespace oop::ode_scal

#endif //EULER_SCAL_HPP