//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>
#include "df_helpers.hpp"

namespace py = pybind11;
namespace oop::bindings {
    void setitem_wrapper(
            oop::stats::DataFrame &self,
            unsigned long long idx,
            sup_arr_types &val) {
        oop::stats::sup_col_types conv_col = transfer_col_ownership(val);
        self.set_column(conv_col, idx);
    }
    void df_setitem(py::class_<oop::stats::DataFrame> &m) {
        m.def("__setitem__", setitem_wrapper,
              py::arg("idx"),
              py::arg("value").noconvert(true));
    }
}
