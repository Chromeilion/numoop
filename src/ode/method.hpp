//
// Created by kiki on 12/24/23.
//

#ifndef METHOD_HPP
#define METHOD_HPP

#include <armadillo>
#include <functional>
#include <iostream>
#include <fstream>

class ODE {
public:
    virtual ~ODE() = default;

    // Templated method for generic types
    template <typename T>
    arma::mat ode(const std::function<arma::vec(double, const arma::vec&)>& f, const T& y0, double h, double end, const std::string& filename = "result.csv") {
        arma::uword steps = static_cast<arma::uword>(end / h) + 1;
        arma::vec t = arma::linspace(0, end, steps);

        arma::mat result_mat(y0.n_elem, steps);
        result_mat.col(0) = arma::conv_to<arma::vec>::from(y0);

        // Call the virtual method
        result_mat = method(f, result_mat, t, h);

        // Saving output data
        arma::mat out = result_mat.t();

        // Append the time vector
        result_mat.insert_rows(0, t.t());

        // Save the result to the specified or default CSV file with a header
        saveToFile(result_mat, t, filename);

        return out;
    }

    // Virtual method
    virtual arma::mat method(const std::function<arma::vec(double, const arma::vec&)>& f, arma::mat& result_mat, const arma::vec& t, double h) const = 0;

private:
    // Save results to file
    void saveToFile(const arma::mat& result_mat, const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "t,y0";
            for (arma::uword i = 1; i < result_mat.n_rows; ++i) {
                file << ",y" << i;
            }
            file << "\n";
            arma::mat mat = result_mat.t();
            mat.save(file, arma::csv_ascii);
            std::cout << "Result saved to " << filename << "\n";
        } else {
            std::cerr << "Error: Unable to open file for writing.\n";
        }
    }
};

#endif // METHOD_HPP
