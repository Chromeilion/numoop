//
// Created by uki on 1/4/24.
//
#ifndef NUMOOP_DATAFRAME_BINDINGS_HPP
#define NUMOOP_DATAFRAME_BINDINGS_HPP

#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace oop::bindings {
    void dataframe_bindings(pybind11::module &);
    void df_init(pybind11::class_<oop::stats::DataFrame> &);
    void df_setitem(pybind11::class_<oop::stats::DataFrame> &);
    void df_getitem(pybind11::class_<oop::stats::DataFrame> &);
    void df_call(pybind11::class_<oop::stats::DataFrame> &);
    void df_get_map(pybind11::class_<oop::stats::DataFrame> &);
    void df_set_map(pybind11::class_<oop::stats::DataFrame> &);
    void df_column_labels(pybind11::class_<oop::stats::DataFrame> &);
    void df_shape(pybind11::class_<oop::stats::DataFrame> &);
    void df_append_row(pybind11::class_<oop::stats::DataFrame> &);
    void df_append_column(pybind11::class_<oop::stats::DataFrame> &);
    void df_insert_column(pybind11::class_<oop::stats::DataFrame> &);
    void df_summarize(pybind11::class_<oop::stats::DataFrame> &);

}

#endif //NUMOOP_DATAFRAME_BINDINGS_HPP
