#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <variant>
#include <functional>
#include <iostream>
#include <cstdlib>
#include <carma>
#include <tuple>
#include "ode/ode_scal.hpp"
#include "ode_types.hpp"
#include "stats/misc.hpp"
#include "wrapper_base.hpp"


namespace py = pybind11;

namespace oop::ode::bindings {
    template <typename C, template<typename>typename CN,
    template<typename, template<typename> typename> typename Wrapper,
            typename InitTypes>
    void MakeBindings(py::module& m, const char* module_name) {
    py::class_<Wrapper<C, CN>>(m, module_name)
        .def(py::init<InitTypes&>())
        .def("ode", &Wrapper<C, CN>::ode);
    }

 }// namespace oop::ode::bindings