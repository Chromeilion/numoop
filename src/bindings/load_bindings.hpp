//
// Created by uki on 1/4/24.
//
#ifndef NUMOOP_LOAD_BINDINGS_HPP
#define NUMOOP_LOAD_BINDINGS_HPP

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace oop::bindings {
    void load_bindings(py::module_ &);
}

#endif //NUMOOP_LOAD_BINDINGS_HPP
