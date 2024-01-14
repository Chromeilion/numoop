#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include "ode/ode_vec.hpp"
#include <carma>
#include <functional>


namespace py = pybind11;
using namespace oop::ode_vec;
using func_vec = std::function<arma::Col<double>(double, const arma::Col<double>&)>;
using y0_vec = arma::Col<double>;

namespace oop::ode::bindings{

// Bindings for the base class
template<typename T = double>
void BindODEVector(py::module &m, const char* classname) {
    py::class_<ODE_Vec<T>>(m, classname)
        .def("ode", &ODE_Vec<T>::ode);
}

// Bindings for the derived class
void BindEulerVector(py::module &m) {
    BindODEVector<double>(m, "ODE_Vec");

    py::class_<Euler<>,ODE_Vec<double>>(m, "Euler")
        .def(py::init<Euler<>::func_vec, y0_vec, double, double>());
}

void BindMidpointVector(py::module &m) {
    //BindODEVector<double>(m, "ODE_Vec_Midpoint");

   py::class_<Midpoint<>,ODE_Vec<double>>(m, "Midpoint")
        .def(py::init<Midpoint<>::func_vec, y0_vec, double, double>());
}

void BindRK4Vector(py::module &m) {
    //BindODEVector<double>(m, "ODE_Vec_RK4");

    py::class_<RK4<>,ODE_Vec<double>>(m, "RK4")
        .def(py::init<RK4<>::func_vec, y0_vec, double, double>());
}
}