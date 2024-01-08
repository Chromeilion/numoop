//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::bindings {
    void df_get_map(py::class_<oop::stats::DataFrame> &m) {
        m.def("get_map",
              &oop::stats::DataFrame::get_map,
              py::arg("idx"),
              R"pbdoc(
Get the integer label map for some column (if there is a mapping).

Parameters
----------
idx : int
    The index of the column from which you want to get a map.

Returns
-------
col_cat_map : dict[int, str]
)pbdoc");
        m.def_property("cat_map",
                       &oop::stats::DataFrame::get_all_maps,
                       &oop::stats::DataFrame::set_all_maps,
                       R"pbdoc(
Get all integer label maps for all columns.

Returns
-------
all_cat_maps : dict[int, dict[int, str]]
    Where the outer dict maps column idx to category maps.
        )pbdoc");
    }
}
