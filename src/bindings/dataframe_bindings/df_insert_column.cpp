//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <carma>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::bindings {
    void df_insert_column(py::class_<oop::stats::DataFrame> &m) {
        m.def("insert_column",
              static_cast<void (oop::stats::DataFrame::*)
                      (oop::stats::sup_col_types&,
                       const arma::uword&,
                       const std::optional<std::string>&)>
              (&oop::stats::DataFrame::insert_column));
        m.def("insert_column",
              static_cast<void (oop::stats::DataFrame::*)
                      (oop::stats::sup_col_types&, const arma::uword&)>
              (&oop::stats::DataFrame::insert_column));
    }

}
