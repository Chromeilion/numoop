//
// Created by uki on 12/31/23.
//
#include <pybind11/pybind11.h>
#include "numoop.hpp"

namespace py = pybind11;

PYBIND11_MODULE(numoop, m) {
    py::class_<oop::stats::DataFrame>(m, "DataFrame")
            .def(py::init<>())
            .def(py::init<std::vector<std::vector<oop::stats::sup_single_types>> &,
                 std::optional<std::vector<std::string>>>(),
                 py::arg("data"), py::arg("labels") = std::nullopt)
            .def("column_labels", &oop::stats::DataFrame::column_labels)
            .def("get_map", &oop::stats::DataFrame::get_map);
    m.def("load", &oop::stats::load);
}


int add(int i, int j) {
    return i + j;
}
