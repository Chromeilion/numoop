//
// Created by uki on 1/4/24.
//
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#include "stats/stats_bindings.hpp"
#include "ode/ode_bindings.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_numoop, m) {
    // DataFrame bindings
    oop::stats::bindings::stats_bindings(m);
    oop::ode::bindings::ode_bindings(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}