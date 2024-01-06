//
// Created by uki on 1/6/24.
//
#include "dataframe_bindings.hpp"
#include <stats/stats.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace oop::bindings {
    void df_insert_row(py::class_<oop::stats::DataFrame> &m) {
        m.def("insert_row", &oop::stats::DataFrame::insert_row,
              py::arg("row"),
              py::arg("idx"),
              R"pbdoc(
Insert a row into the DataFrame.

Parameters
----------
row : list
idx : unsigned int
)pbdoc");
    }
}