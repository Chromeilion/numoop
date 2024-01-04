//
// Created by uki on 1/4/24.
//
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#include "dataframe_bindings/dataframe_bindings.hpp"
#include "load_bindings.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_numoop, m) {
    // DataFrame bindings
    oop::bindings::dataframe_bindings(m);
    // Load function bindings
    oop::bindings::load_bindings(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}