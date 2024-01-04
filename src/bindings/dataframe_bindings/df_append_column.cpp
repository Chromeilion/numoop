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
    void df_append_column(py::class_<oop::stats::DataFrame> &m) {
        m.def("append_column",
              static_cast<void (oop::stats::DataFrame::*)
                      (oop::stats::sup_col_types&,
                              const std::optional<std::string>&)>
              (&oop::stats::DataFrame::append_column));
        m.def("append_column",
              static_cast<void (oop::stats::DataFrame::*)
                      (oop::stats::sup_col_types&)>
                      (&oop::stats::DataFrame::append_column));
    }
}
