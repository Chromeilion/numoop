//
// Created by kiki on 12/24/23.
//

#ifndef MIDPOINT_HPP
#define MIDPOINT_HPP

#include <ode/method.hpp>

class Midpoint : public ODE {

public:

    // Implement Midpoint method for vector case
    arma::mat method_vec(arma::mat& result_mat, const arma::vec& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::vec k1 = h * f_vec(t(i - 1), result_mat.col(i - 1));
            arma::vec k2 = h * f_vec(t(i - 1) + h / 2, result_mat.col(i - 1) + k1 / 2);

            result_mat.col(i) = result_mat.col(i - 1) + k2;
        }
        save_vec(result_mat, t, "result_midpoint_vector.csv");
        return result_mat;
    }

    // Implementation for scalar case
    arma::mat method_scalar(arma::mat& result_mat, const arma::vec& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            double k1 = h * f_scal(t(i - 1), result_mat(0,i - 1));
            double k2 = h * f_scal(t(i - 1) + h / 2, result_mat(0,i - 1) + k1 / 2);

            result_mat(0,i) = result_mat(0,i - 1) + k2;
        }
        save_scalar(result_mat, t, "result_midpoint_scalar.csv");
        return result_mat;
    }
};

#endif //MIDPOINT_HPP