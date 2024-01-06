//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <stats/stats.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "df_helpers.hpp"

namespace py = pybind11;
namespace oop::bindings {
    void insert_col_wrapper(
            oop::stats::DataFrame &self,
            sup_arr_types &col,
            const arma::uword &idx,
            const std::optional<std::string> &label=std::nullopt) {
        auto conv_col = transfer_col_ownership(col);
        self.insert_column(conv_col, idx, label);
    }
    void df_insert_column(py::class_<oop::stats::DataFrame> &m) {
        m.def("insert_column", &insert_col_wrapper,
              py::arg("col"),
              py::arg("idx"),
              py::arg("label")=std::nullopt);
    }
}
