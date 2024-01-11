//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <stats/stats.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace oop::stats::bindings {
    void df_repr(py::class_<oop::stats::DataFrame> &m) {
        m.def("__repr__", [](oop::stats::DataFrame &self){
            auto shape = self.shape();
            auto rows = std::to_string(shape.first);
            auto cols = std::to_string(shape.second);
            return "<numoop.DataFrame with shape (" + rows + ", " + cols + ")";
            });
    }
}