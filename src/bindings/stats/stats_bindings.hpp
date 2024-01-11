//
// Created by uki on 1/11/24.
//

#ifndef NUMOOP_STATS_BINDINGS_HPP
#define NUMOOP_STATS_BINDINGS_HPP
#include <pybind11/pybind11.h>

namespace oop::stats::bindings {
    void stats_bindings(pybind11::module_ &m);
}

#endif //NUMOOP_STATS_BINDINGS_HPP
