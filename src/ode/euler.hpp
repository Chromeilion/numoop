//
// Created by kiki on 12/24/23.
//

#ifndef EULER_HPP
#define EULER_HPP

#include <ode/method.hpp>

class Euler : public ODE {
public:
    template <typename T1, typename T2>
    // Implement Euler method
    arma::mat method(const std::function<arma::vec(T1, const T2&)>& f, arma::mat& result_mat, const arma::vec& t, double h) const override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat.col(i) = result_mat.col(i - 1) + h * f(t(i), result_mat.col(i - 1));
        }
        return result_mat;
    }
};

#endif //EULER_HPP