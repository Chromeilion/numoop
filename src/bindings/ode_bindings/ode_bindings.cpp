#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <ode/ode_scal.hpp>
#include "scal_bindings.hpp"
#include "vector_bindings.hpp"
#include "ode_bindings.hpp"
#include <carma>

namespace py = pybind11;
namespace oop::ode::bindings {

    void ode_bindings(py::module& m){

        BindEulerScalar(m);
        BindEulerVector(m);
    }

} // namespace oop::ode::bindings