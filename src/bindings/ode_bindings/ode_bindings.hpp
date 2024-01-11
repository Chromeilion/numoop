#ifndef ODE_BINDINGS_HPP
#define ODE_BINDINGS_HPP

#include <pybind11/pybind11.h>

namespace oop::ode::bindings {
    void ode_bindings(pybind11::module& m);
}

#endif //ODE_BINDINGS_HPP