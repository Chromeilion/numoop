#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <ode/ode_scal.hpp>
#include "ode_types.hpp"
#include "scal_bindings.hpp"
#include "ode_bindings.hpp"
#include <variant>

namespace py = pybind11;
namespace oop::ode::bindings {

    void ode_bindings(py::module& m){

        MakeBindings(m, "Euler_Scal");
        //MakeBindings(m, "Midpoint_Scal")
    }

} // namespace oop::ode::bindings