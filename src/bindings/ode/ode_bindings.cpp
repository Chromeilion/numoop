#include <pybind11/pybind11.h>
#include "scal_bindings.hpp"
#include "ode_bindings.hpp"
#include "wrapper_vec.hpp"
#include "wrapper_scal.hpp"
#include <variant>


namespace py = pybind11;
namespace oop::ode::bindings {
    void ode_bindings(py::module& m){
        // Scalar methods
        MakeBindings<sup_scal_euler, oop::ode_scal::Euler_Scal, ScalWrap,
        sup_scal_init_types>(m,"Euler_Scal");
        MakeBindings<sup_scal_midpoint, oop::ode_scal::Midpoint_Scal, ScalWrap,
        sup_scal_init_types >(m, "Midpoint_Scal");
        MakeBindings<sup_scal_rk4, oop::ode_scal::RK4_Scal, ScalWrap,
        sup_scal_init_types >(m, "RK4_Scal");

        // Vector methods
        MakeBindings<sup_vec_euler, oop::ode_vec::Euler, VecWrap,
                sup_vec_init_types>(m, "Euler");
        MakeBindings<sup_vec_midpoint, oop::ode_vec::Midpoint, VecWrap,
                sup_vec_init_types>(m, "Midpoint");
        MakeBindings<sup_vec_rk4, oop::ode_vec::RK4, VecWrap,
                sup_vec_init_types>(m, "RK4");
    }
} // namespace oop::ode::bindings