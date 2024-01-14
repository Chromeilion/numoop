#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include "ode/ode_scal.hpp"


namespace py = pybind11;
using namespace oop::ode_scal;
using func_scal = std::function<double(double,double)>;

namespace oop::ode::bindings{

// Bindings for the base class
template<typename T = double>
void BindODEScalar(py::module &m, const char* classname) {
    py::class_<ODE_Scal<T>>(m, classname)
        .def("ode", &ODE_Scal<T>::ode);
}

// Bindings for the derived class
void BindEulerScalar(py::module &m) {
    BindODEScalar<double>(m, "ODE_Scal");

    py::class_<Euler_Scal<>,ODE_Scal<double>>(m, "Euler_Scal")
        .def(py::init<Euler_Scal<>::func_scal, double, double, double>());
}

void BindMidpointScalar(py::module &m) {
//    BindODEScalar<double>(m, "ODE_Scal_Midpoint");

    py::class_<Midpoint_Scal<>,ODE_Scal<double>>(m, "Midpoint_Scal")
        .def(py::init<Midpoint_Scal<>::func_scal, double, double, double>());
}

void BindRK4Scalar(py::module &m) {
    //BindODEScalar<double>(m, "ODE_Scal_RK4");

    py::class_<RK4_Scal<>,ODE_Scal<double>>(m, "RK4_Scal")
        .def(py::init<RK4_Scal<>::func_scal, double, double, double>());
}
}