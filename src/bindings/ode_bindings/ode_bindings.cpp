#include <pybind11/pybind11.h>
#include <ode/ode_scal.hpp>
#include "method_scal_bindings.hpp"
#include "ode_bindings.hpp"

namespace py = pybind11;
namespace oop::ode::bindings {
    void ode_bindings(py::module& m){
    oop::ode::bindings::bind_ode_scal(m);
    oop::ode::bindings::bind_ode_vec(m);
    oop::ode::bindings::bind_euler_scal(m);
    }
} // namespace oop::ode::bindings