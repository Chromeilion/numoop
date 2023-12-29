//
// Created by kiki on 12/24/23.
//

#ifndef EULER_HPP
#define EULER_HPP

#include <ode/method.hpp>

namespace oop::ode{
    
class Euler : public ODE {

public:

    // Implement Euler method for vector case
    arma::mat method_vec(arma::mat& result_mat, const arma::vec& t) override {       
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat.col(i) = result_mat.col(i - 1) + h * f_vec(t(i), result_mat.col(i - 1));
        }
        save_vec(result_mat, t, "result_euler_vector.csv");
        return result_mat;
    }

    // Implementation for scalar case
    arma::mat method_scalar(arma::mat& result_mat, const arma::vec& t) override {
        for (arma::uword i = 1; i < t.n_elem; ++i) {
            result_mat(0,i) = result_mat(0,i-1) + h * f_scal(t(i), result_mat(0,i-1));
        }
        save_scalar(result_mat, t, "result_euler_scalar.csv");
        return result_mat;
    }
};
}
#endif //EULER_HPP