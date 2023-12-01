//
// Created by uki on 11/30/23.
//

#ifndef EXAMPLES_DATAFRAME_HPP
#define EXAMPLES_DATAFRAME_HPP
#include <vector>
#include <string>
#include <variant>
#include <armadillo>
#include "dataframe_helpers.hpp"

namespace oop::stats {
    // All supported column types.
    typedef std::variant <arma::dcolvec, arma::cx_dcolvec, arma::cx_fcolvec,
            arma::ucolvec, arma::icolvec> sup_col_types;

    // All supported single value types.
    typedef std::variant<double, arma::cx_double, arma::cx_float,
            arma::uword, arma::sword> sup_single_types;

    class DataFrame {
    private:
        // Each column in the dataframe is represented by an armadillo Col
        // object which can hold most types minus strings.
        std::vector<sup_col_types> columns;
        std::vector<std::string> _column_types;

    public:
        // Get what type each column has.
        std::vector<std::string>& column_types() {return _column_types;};

        // Shape of the matrix
        std::pair<unsigned int, unsigned int> shape;

        // Indexing
        sup_col_types &operator[](std::size_t idx) { return columns[idx]; }

        // Append a row to the bottom of the dataframe.
        void append_row(std::vector<sup_single_types> append_data) {
            auto _ = [](auto row, auto item){throw std::runtime_error("Two types did not match when appending a row");};
            for (unsigned int i; i < this->shape.second; ++i) {
                std::visit(
                        overloaded{oop::stats::InsertRow(), _},
                        (*this)[i], append_data[i]);
            }
        };
    };
}

#endif //EXAMPLES_DATAFRAME_HPP
