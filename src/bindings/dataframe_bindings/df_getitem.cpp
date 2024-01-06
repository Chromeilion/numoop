//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::bindings {
    void df_getitem(py::class_<oop::stats::DataFrame> &m) {
        m.def("__getitem__",
              [](oop::stats::DataFrame &self, unsigned &index)
              { return self[index]; },
              py::return_value_policy::copy);
    }
}
