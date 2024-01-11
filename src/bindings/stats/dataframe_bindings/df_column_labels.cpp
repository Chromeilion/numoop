//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::stats::bindings {
    void df_column_labels(py::class_<oop::stats::DataFrame> &m) {
        m.def_property("column_labels",
                       &oop::stats::DataFrame::column_labels,
                       &oop::stats::DataFrame::set_column_labels,
                       R"pbdoc(
The labels for each column if they are present. When setting the
labels, there must be a label for each column.

Returns
-------
column_labels : list[str]
)pbdoc");
    }

}
