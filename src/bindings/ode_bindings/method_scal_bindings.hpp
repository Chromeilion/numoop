#ifndef METHOD_SCAL_BINDINGS_HPP
#define METHOD_SCAL_BINDINGS_HPP

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace oop::ode::bindings {
    void bind_ode_scal(py::module& m);
    void bind_ode_vec(py::module& m);
    void bind_euler_scal(py::module& m);
}

#endif //METHOD_SCAL_BINDINGS_HPP
