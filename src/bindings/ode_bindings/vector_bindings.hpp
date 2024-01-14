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
    py::class_<ODE_Vec<T>>(m, classname,
                           R"pbdoc(
Base vector ODE solver.
)pbdoc")
        .def("ode", &ODE_Vec<T>::ode,
        R"pbdoc(
Solve the ODE using the selected method.
Prints the output in a CSV.

Returns
-------
sol : numpy.ndarray
    Solution of the ODE at each given time.
)pbdoc");
}

// Bindings for the derived class
void BindEulerVector(py::module &m) {
    BindODEVector<double>(m, "PyODE_Vec");

    py::class_<Euler<>,ODE_Vec<double>>(m, "PyEuler",
                                        R"pbdoc(
Euler ODE vector solver.
)pbdoc")
        .def(py::init<Euler<>::
        func_vec, 
        y0_vec, 
        double, 
        double>(),
        R"pbdoc(
Constructor for the class representing the Euler method.

Parameters
----------
func : Callable[[float, numpy.ndarray], numpy.ndarray]
    The function on which you want to perform the ODE.
y0 : numpy.ndarray
    The starting point of the ODE.
h : float
    The step considered for the ODE.
end : float
    The final time of the ODE.
)pbdoc");
}

void BindMidpointVector(py::module &m) {

   py::class_<Midpoint<>,ODE_Vec<double>>(m, "PyMidpoint",
                                          R"pbdoc(
Midpoint ODE vector solver.
)pbdoc")
        .def(py::init<Midpoint<>::
        func_vec, 
        y0_vec, 
        double, 
        double>(),
        R"pbdoc(
Constructor for the class representing the Midpoint method.

Parameters
----------
func : Callable[[float, numpy.ndarray], numpy.ndarray]
    The function on which you want to perform the ODE.
y0 : numpy.ndarray
    The starting point of the ODE.
h : float
    The step considered for the ODE.
end : float
    The final time of the ODE.
)pbdoc");
}

void BindRK4Vector(py::module &m) {

    py::class_<RK4<>,ODE_Vec<double>>(m, "PyRK4",
                                      R"pbdoc(
RK4 ODE vector solver.
)pbdoc")
        .def(py::init<RK4<>::
        func_vec, 
        y0_vec, 
        double, 
        double>(),
        R"pbdoc(
Constructor for the class representing the Runge-Kutta 4 method.

Parameters
----------
func : Callable[[float, numpy.ndarray], numpy.ndarray]
    The function on which you want to perform the ODE.
y0 : numpy.ndarray
    The starting point of the ODE.
h : float
    The step considered for the ODE.
end : float
    The final time of the ODE.
)pbdoc");
}
}