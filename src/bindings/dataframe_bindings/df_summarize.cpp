//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_summarize(py::class_<oop::stats::DataFrame> &m) {
        m.def("summarize", &oop::stats::DataFrame::summarize);
    }
}
