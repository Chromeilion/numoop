//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_append_row(py::class_<oop::stats::DataFrame> &m) {
        m.def("append_row",
              &oop::stats::DataFrame::append_row);
    }
}
