//
// Created by kiki on 12/24/23.
//

#ifndef RK4_HPP
#define RK4_HPP

#include <ode/method.hpp>

namespace rk4 {

class RungeKutta4 : public ODE {
    
public:

    // Implement Runge-Kutta 4 method
    arma::mat method(const std::function<arma::vec(double, const arma::vec&)>& f, arma::mat& result_mat, const arma::vec& t, double h) const override {
        
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::vec k1 = h * f(t(i - 1), result_mat.col(i - 1));
            arma::vec k2 = h * f(t(i - 1) + h / 2, result_mat.col(i - 1) + k1 / 2);
            arma::vec k3 = h * f(t(i - 1) + h / 2, result_mat.col(i - 1) + k2 / 2);
            arma::vec k4 = h * f(t(i - 1) + h, result_mat.col(i - 1) + k3);

            result_mat.col(i) = result_mat.col(i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        }
        return result_mat;
    }
};

} // namespace rk4

#endif //RK4_HPP