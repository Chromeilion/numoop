//
// Created by uki on 1/4/24.
//
#ifndef NUMOOP_LOAD_BINDINGS_HPP
#define NUMOOP_LOAD_BINDINGS_HPP

#include <pybind11/pybind11.h>
#include "load_bindings.hpp"

namespace oop::stats::bindings {
    void load_bindings(pybind11::module_ &);
}

#endif //NUMOOP_LOAD_BINDINGS_HPP
