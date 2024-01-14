#include <pybind11/pybind11.h>
#include "scal_bindings.hpp"
#include "vector_bindings.hpp"
#include "ode_bindings.hpp"


namespace py = pybind11;
namespace oop::ode::bindings {

    void ode_bindings(py::module& m){
        BindEulerScalar(m);
        BindEulerVector(m);
        BindMidpointScalar(m);
        BindMidpointVector(m);
        BindRK4Scalar(m);
        BindRK4Vector(m);
    }

} // namespace oop::ode::bindings