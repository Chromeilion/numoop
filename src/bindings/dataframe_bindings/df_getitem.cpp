//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_getitem(py::class_<oop::stats::DataFrame> &m) {
        m.def("__getitem__",
              [](oop::stats::DataFrame &self, unsigned index)
              { return self[index]; });
    }
}
