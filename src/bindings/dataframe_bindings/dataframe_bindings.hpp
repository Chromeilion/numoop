//
// Created by uki on 1/4/24.
//
#ifndef NUMOOP_DATAFRAME_BINDINGS_HPP
#define NUMOOP_DATAFRAME_BINDINGS_HPP

#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;

namespace oop::bindings {
    void dataframe_bindings(py::module &);
    void df_init(py::class_<oop::stats::DataFrame> &);
    void df_setitem(py::class_<oop::stats::DataFrame> &);
    void df_getitem(py::class_<oop::stats::DataFrame> &);
    void df_call(py::class_<oop::stats::DataFrame> &);
    void df_get_map(py::class_<oop::stats::DataFrame> &);
    void df_set_map(py::class_<oop::stats::DataFrame> &);
    void df_column_labels(py::class_<oop::stats::DataFrame> &);
    void df_shape(py::class_<oop::stats::DataFrame> &);
    void df_append_row(py::class_<oop::stats::DataFrame> &);
    void df_append_column(py::class_<oop::stats::DataFrame> &);
    void df_insert_column(py::class_<oop::stats::DataFrame> &);
    void df_summarize(py::class_<oop::stats::DataFrame> &);

}

#endif //NUMOOP_DATAFRAME_BINDINGS_HPP
