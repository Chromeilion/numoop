#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include "ode/ode_vec.hpp"
#include <carma>
#include <functional>


namespace py = pybind11;
using namespace oop::ode_vec;
using func_vec = std::function<arma::Col<double>(double, const arma::Col<double>&)>;

namespace oop::ode::bindings{

// Bindings for the base class
template<typename T = double>
void BindODEVector(py::module &m, const char* classname) {
    py::class_<ODE_Vec<T>>(m, classname)
        .def("set_func", &ODE_Vec<T>::set_func)
        .def("set_y0", &ODE_Vec<T>::set_y0)
        .def("set_h", &ODE_Vec<T>::set_h)
        .def("set_end", &ODE_Vec<T>::set_end)
        .def("ode", &ODE_Vec<T>::ode);
}

// Bindings for the derived class
void BindEulerVector(py::module &m) {
    BindODEVector<double>(m, "ODE_Vec_double");

    py::class_<Euler<>,ODE_Vec<double>>(m, "Euler")
        .def(py::init<Euler<>::func_vec, arma::Col<double>, double, double>());
}
}