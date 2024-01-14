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
        .def("set_func", &ODE_Scal<T>::set_func)
        .def("set_y0", &ODE_Scal<T>::set_y0)
        .def("set_h", &ODE_Scal<T>::set_h)
        .def("set_end", &ODE_Scal<T>::set_end)
        .def("ode", &ODE_Scal<T>::ode);
}

// Bindings for the derived class
void BindEulerScalar(py::module &m) {
    BindODEScalar<double>(m, "ODE_Scal_double");

    py::class_<Euler_Scal<>,ODE_Scal<double>>(m, "Euler_Scal")
        .def(py::init<Euler_Scal<>::func_scal, double, double, double>());
}
}