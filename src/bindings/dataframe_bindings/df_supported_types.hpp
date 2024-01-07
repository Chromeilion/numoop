//
// Created by uki on 1/5/24.
//

#ifndef NUMOOP_SUPPORTED_TYPES_HPP
#define NUMOOP_SUPPORTED_TYPES_HPP
#include <variant>
#include <armadillo>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>

namespace py=pybind11;
namespace oop::bindings {
    // All Numpy datatypes that work with Numoop.
    typedef std::variant<
            py::array_t<double>,
            py::array_t<long long>,
            py::array_t<long>,
            py::array_t<float>,
            py::array_t<unsigned long>,
            py::array_t<unsigned long long>,
            py::array_t<std::complex<double>>,
            py::array_t<std::complex<float>>> sup_arr_types;
}

#endif //NUMOOP_SUPPORTED_TYPES_HPP
