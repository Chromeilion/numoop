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
    void df_setitem(py::class_<oop::stats::DataFrame> &m) {
        m.def("__setitem__",
              [](oop::stats::DataFrame &self,
                 unsigned index,
                 oop::stats::sup_col_types &val){ self[index] = val; });
    }
}
