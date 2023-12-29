//
// Created by kiki on 12/24/23.
//

#ifndef RK4_HPP
#define RK4_HPP

#include <ode/method.hpp>

namespace oop::ode{

class RungeKutta4 : public ODE {

public:

    // Implement Runge-Kutta 4 method for vector case
    arma::mat method_vec(arma::mat& result_mat, const arma::vec& t) override {
        
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::vec k1 = h * f_vec(t(i - 1), result_mat.col(i - 1));
            arma::vec k2 = h * f_vec(t(i - 1) + h / 2, result_mat.col(i - 1) + k1 / 2);
            arma::vec k3 = h * f_vec(t(i - 1) + h / 2, result_mat.col(i - 1) + k2 / 2);
            arma::vec k4 = h * f_vec(t(i - 1) + h, result_mat.col(i - 1) + k3);

            result_mat.col(i) = result_mat.col(i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        }
        save_vec(result_mat, t, "result_rk4_vector.csv");
        return result_mat;
    }

    // Implementation for scalar case
    arma::mat method_scalar(arma::mat& result_mat, const arma::vec& t) override {

        for (arma::uword i = 1; i < t.n_elem; ++i) {
            double k1 = h * f_scal(t(i - 1), result_mat(0,i - 1));
            double k2 = h * f_scal(t(i - 1) + h / 2, result_mat(0,i - 1) + k1 / 2);
            double k3 = h * f_scal(t(i - 1) + h / 2, result_mat(0,i - 1) + k2 / 2);
            double k4 = h * f_scal(t(i - 1) + h, result_mat(0,i - 1) + k3);

            result_mat(0,i) = result_mat(0,i - 1) + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        }
        save_scalar(result_mat, t, "result_rk4_scalar.csv");
        return result_mat;

    }
};
}
#endif //RK4_HPP