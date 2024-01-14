//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::stats::bindings {
    void dataframe_bindings(py::module &m) {
        py::class_<oop::stats::DataFrame> df = py::class_<oop::stats::DataFrame>(
                m, "PyDataFrame",
                R"pbdoc(
Python bindings for the oop::stats::DataFrame object.
)pbdoc"
    );
        df_init(df);
        df_setitem(df);
        df_getitem(df);
        df_call(df);
        df_get_map(df);
        df_set_map(df);
        df_column_labels(df);
        df_shape(df);
        df_append_row(df);
        df_insert_row(df);
        df_append_column(df);
        df_insert_column(df);
        df_summarize(df);
        df_view(df);
        df_pickle(df);
        df_repr(df);
    }
}
