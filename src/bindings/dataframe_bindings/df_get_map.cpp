//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_get_map(py::class_<oop::stats::DataFrame> &m) {
        m.def("get_map", &oop::stats::DataFrame::get_map);
    }
}
