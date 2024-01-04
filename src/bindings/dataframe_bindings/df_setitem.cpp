//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_setitem(py::class_<oop::stats::DataFrame> &m) {
        m.def("__setitem__",
              [](oop::stats::DataFrame &self,
                 unsigned index,
                 oop::stats::sup_col_types &val){ self[index] = val; });
    }
}
