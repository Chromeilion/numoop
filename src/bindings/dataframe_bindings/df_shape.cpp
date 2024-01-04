//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_shape(py::class_<oop::stats::DataFrame> &m) {
        m.def_property_readonly("shape",
                                &oop::stats::DataFrame::shape);
    }

}
