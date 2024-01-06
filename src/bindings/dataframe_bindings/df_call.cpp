//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include "df_helpers.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::bindings {
    void df_call(py::class_<oop::stats::DataFrame> &m) {
        m.def("__call__",
              [](oop::stats::DataFrame &self, std::string& label)
              { return convert_col(self(label)); });
    }
}
