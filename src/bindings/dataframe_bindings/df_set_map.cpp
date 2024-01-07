//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::bindings {
    void df_set_map(py::class_<oop::stats::DataFrame> &m) {
        m.def("set_map",
              &oop::stats::DataFrame::set_map,
              py::arg("idx"),
              py::arg("map"),
              R"pbdoc(
Set a integer-string mapping for a specific column.

Parameters
----------
idx : unsigned int
map : dict[int, str]
)pbdoc");
    }
}
