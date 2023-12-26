//
// Created by kiki on 12/24/23.
//

#ifndef MIDPOINT_HPP
#define MIDPOINT_HPP

#include <ode/method.hpp>

namespace midpoint {

class Midpoint : public ODE {
public:
    template <typename T>
    // Implement Midpoint method
    arma::mat method(const std::function<arma::vec(double, const T&)>& f, arma::mat& result_mat, const arma::vec& t, double h) const override {

        for (arma::uword i = 1; i < t.n_elem; ++i) {
            arma::vec k1 = h * f(t(i - 1), result_mat.col(i - 1));
            arma::vec k2 = h * f(t(i - 1) + h / 2, result_mat.col(i - 1) + k1 / 2);

            result_mat.col(i) = result_mat.col(i - 1) + k2;
        }
        return result_mat;
    }
};

} // namespace midpoint

#endif //MIDPOINT_HPP