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

        MakeBindings<sup_scal_euler>(m,"Euler_Scal");
        MakeBindings<sup_scal_midpoint>(m, "Midpoint_Scal");
        MakeBindings<sup_scal_rk4>(m, "RK4_Scal");
    }

} // namespace oop::ode::bindings