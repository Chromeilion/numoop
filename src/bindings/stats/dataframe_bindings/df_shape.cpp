//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::stats::bindings {
    void df_shape(py::class_<oop::stats::DataFrame> &m) {
        m.def_property_readonly("shape",
                                &oop::stats::DataFrame::shape,
                                R"pbdoc(
Number of rows and columns in the DataFrame.

Returns
-------
shape : tuple[int, int]
)pbdoc");
    }

}
