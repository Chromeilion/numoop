#ifndef METHOD_SCAL_BINDINGS_HPP
#define METHOD_SCAL_BINDINGS_HPP

#include <pybind11/pybind11.h>

namespace oop::bindings_ode {
    void bind_ode_scal(py::module& m, const std::string& suffix = "");
}

#endif //METHOD_SCAL_BINDINGS_HPP
