//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include "df_helpers.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::stats::bindings {
    void df_getitem(py::class_<oop::stats::DataFrame> &m) {
        m.def("__getitem__", [](oop::stats::DataFrame &self, unsigned &idx){
            return convert_col(self[idx]);
        },
              py::arg("col_idx"));
    }
}
