//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_set_map(py::class_<oop::stats::DataFrame> &m) {
        m.def("set_map", &oop::stats::DataFrame::set_map);
    }
}
