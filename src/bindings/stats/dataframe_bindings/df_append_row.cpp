//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::stats::bindings {
    void df_append_row(py::class_<oop::stats::DataFrame> &m) {
        // Because the append_row method creates a copy of the data being
        // inserted, we don't need to worry about memory ownership like we do
        // in some other methods.
        m.def("append_row",
              &oop::stats::DataFrame::append_row,
              py::arg("row").noconvert(true),
              R"pbdoc(
Append a row to the DataFrame. Must have a correct amount of
columns and the data types must match the current column dtypes.

Parameters
----------
row : list or list[list] or numpy.ndarray
    A list with len 3 has 3 columns.
)pbdoc");
    }
}
