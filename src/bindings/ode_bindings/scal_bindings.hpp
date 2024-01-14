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
    py::class_<ODE_Scal<T>>(m, classname, R"pbdoc(
Base ODE scalar class.
)pbdoc"
            )
        .def("ode", &ODE_Scal<T>::ode,
        R"pbdoc(
Solve the ODE using the selected method.
Prints the output in a CSV.

Returns
-------
sol : numpy.ndarray
    Solution of the scalar ODE at each given time.
)pbdoc");
}

// Bindings for the derived class
void BindEulerScalar(py::module &m) {
    BindODEScalar<double>(m, "PyODE_Scal");

    py::class_<Euler_Scal<>,ODE_Scal<double>>(m, "PyEuler_Scal",
                                              R"pbdoc(
Eular scalar ODE solver.
)pbdoc")
        .def(py::init<Euler_Scal<>::
            func_scal, 
            double, 
            double, 
            double>(),
            py::arg("func"), py::arg("y0"), py::arg("h"),
            py::arg("end"),
            R"pbdoc(
Constructor for the class representing the scalar case of the Euler method.

Parameters
----------
func : Callable[[float, float], float]
    The function on which you want to perform the ODE.
y0 : float
    The starting point of the ODE.
h : float
    The step considered for the ODE.
end : float
    The final time of the ODE.
)pbdoc");
}

void BindMidpointScalar(py::module &m) {
//    BindODEScalar<double>(m, "ODE_Scal_Midpoint");

    py::class_<Midpoint_Scal<>,ODE_Scal<double>>(m, "PyMidpoint_Scal",
                                                 R"pbdoc(
Midpoint scalar ODE solver.
)pbdoc")
        .def(py::init<Midpoint_Scal<>::
            func_scal, 
            double, 
            double, 
            double>(),
            py::arg("func"), py::arg("y0"), py::arg("h"), py::arg("end"),
            R"pbdoc(
Constructor for the class representing the scalar case of the Midpoint method.

Parameters
----------
func : Callable[[float, float], float]
    The function on which you want to perform the ODE.
y0 : float
    The starting point of the ODE.
h : float
    The step considered for the ODE.
end : float
    The final time of the ODE.
)pbdoc");
}

void BindRK4Scalar(py::module &m) {
    //BindODEScalar<double>(m, "ODE_Scal_RK4");

    py::class_<RK4_Scal<>,ODE_Scal<double>>(m, "PyRK4_Scal",
                                            R"pbdoc(
RK4 scalar ODE solver.
)pbdoc")
        .def(py::init<RK4_Scal<>::
            func_scal,
            double, 
            double,
            double>(),
            py::arg("func"), py::arg("y0"), py::arg("h"), py::arg("end"),
            R"pbdoc(
Constructor for the class representing the scalar case of the RK4 method.

Parameters
----------
func : Callable[[float, float], float] or str
    The function on which you want to perform the ODE.
y0 : float
    The starting point of the ODE.
h : float
    The step considered for the ODE.
end : float
    The final time of the ODE.
)pbdoc");
}
}