//
// Created by uki on 1/6/24.
//
#include "df_helpers.hpp"
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <carma>

namespace oop::stats::bindings {
    class ConvertArray {
    public:
        template<typename T>
        oop::stats::sup_col_types operator()(py::array_t<T> &col) {
            return carma::arr_to_col(col, true);
        }
    };
    // Convert numpy arrays to armadillo columns. This function takes ownership
    // of the array by copying all data.
    oop::stats::sup_col_types transfer_col_ownership(sup_arr_types &col) {
        // Convert the array
        oop::stats::sup_col_types new_col = std::visit(ConvertArray(), col);
        return new_col;
    }
    sup_arr_types convert_col(oop::stats::sup_col_types &col) {
        return std::visit(
                [](auto &c){return sup_arr_types{carma::col_to_arr(c, true)};},
                col);
    }
}
