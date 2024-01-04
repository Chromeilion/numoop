//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_call(py::class_<oop::stats::DataFrame> &m) {
        m.def("__call__",
              [](oop::stats::DataFrame &self, std::string& label)
              { return self(label); });
    }

}
