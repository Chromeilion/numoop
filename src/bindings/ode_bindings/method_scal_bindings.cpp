#include <pybind11/pybind11.h>
#include <ode/ode_scal.hpp>
#include "method_scal_bindings.hpp"

namespace py = pybind11;
namespace oop::ode::bindings {
    template <typename T>
    void bind_ode_scal(py::module& m) {
        py::class_<ODE_Scal<T>>(m, ("ODE_Scal" + suffix).c_str())
            .def(py::init<typename ODE_Scal<T>::func_scal, T, T, T>(),
                 py::arg("f") = nullptr, py::arg("y0") = T{}, py::arg("h") = T{}, py::arg("end") = T{})
            .def("set_func", &ODE_Scal<T>::set_func, py::arg("new_func"))
            .def("set_y0", &ODE_Scal<T>::set_y0, py::arg("new_y0"))
            .def("set_h", &ODE_Scal<T>::set_h, py::arg("new_h"))
            .def("set_end", &ODE_Scal<T>::set_end, py::arg("new_end"))
            .def("ode", &ODE_Scal<T>::ode)
    }
} // namespace oop::ode::bindings