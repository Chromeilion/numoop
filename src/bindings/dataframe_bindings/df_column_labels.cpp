//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"

namespace oop::bindings {
    void df_column_labels(py::class_<oop::stats::DataFrame> &m) {
        m.def_property("column_labels",
                       &oop::stats::DataFrame::column_labels,
                       &oop::stats::DataFrame::set_column_labels);
    }

}
