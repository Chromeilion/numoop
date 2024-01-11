//
// Created by uki on 1/4/24.
//
#ifndef NUMOOP_DATAFRAME_BINDINGS_HPP
#define NUMOOP_DATAFRAME_BINDINGS_HPP

#include <carma>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace oop::stats::bindings {
    // All Numpy datatypes that work with Numoop.
    typedef std::variant<
            py::array_t<int>,
            py::array_t<long int>,
            py::array_t<long long int>,
            py::array_t<float>,
            py::array_t<double>,
            py::array_t<unsigned int>,
            py::array_t<unsigned long int>,
            py::array_t<unsigned long long int>,
            py::array_t<std::complex<double>>,
            py::array_t<std::complex<float>>> sup_arr_types;

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
    void df_insert_row(pybind11::class_<oop::stats::DataFrame> &m);
    void df_append_column(pybind11::class_<oop::stats::DataFrame> &);
    void df_insert_column(pybind11::class_<oop::stats::DataFrame> &);
    void df_summarize(pybind11::class_<oop::stats::DataFrame> &);
    void df_view(pybind11::class_<oop::stats::DataFrame> &);
    void df_pickle(pybind11::class_<oop::stats::DataFrame> &m);
    void df_repr(py::class_<oop::stats::DataFrame> &m);
}

#endif //NUMOOP_DATAFRAME_BINDINGS_HPP
