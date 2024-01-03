//
// Created by uki on 12/31/23.
//
#include <carma>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <numoop.hpp>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(_numoop, m) {
    py::class_<oop::stats::DataFrame>(m, "DataFrame")
            .def(py::init<>())
            .def(py::init<std::vector<std::vector<oop::stats::sup_single_types>> &,
                 std::optional<std::vector<std::string>>>(),
                 py::arg("data"), py::arg("labels") = std::nullopt)
            .def("__setitem__",
                 [](oop::stats::DataFrame &self, unsigned index,
                         oop::stats::sup_col_types &val){ self[index] = val; })
            .def("__getitem__", [](oop::stats::DataFrame &self, unsigned index)
             { return self[index]; })
            .def("__call__", [](oop::stats::DataFrame &self, std::string& label)
            { return self(label); })
            .def("get_map", &oop::stats::DataFrame::get_map)
            .def("set_map", &oop::stats::DataFrame::set_map)
            .def_property("column_labels", &oop::stats::DataFrame::column_labels,
                          &oop::stats::DataFrame::set_column_labels)
            .def_property_readonly("shape", &oop::stats::DataFrame::shape);

    m.def("load", static_cast<std::vector<std::string> (*)(
            const std::string&,
            oop::stats::DataFrame&,
            std::optional<bool>,
            const std::optional<std::vector<int>>&,
            std::optional<std::vector<oop::stats::convert_func>>,
            std::optional<char>, std::optional<char>)>(&oop::stats::load),
          "Load a CSV into a DataFrame",
          py::arg("filepath"),
          py::arg("dataframe"),
          py::arg("header") = std::nullopt,
          py::arg("columns") = std::nullopt,
          py::arg("col_types") = std::nullopt,
          py::arg("newline_delimiter") = std::nullopt,
          py::arg("column_delimiter") = std::nullopt
          );
    m.def("load", static_cast<std::pair<std::vector<std::string>,
            oop::stats::DataFrame> (*)(
                  const std::string&,
                  std::optional<bool>,
                  const std::optional<std::vector<int>>&,
                  std::optional<std::vector<oop::stats::convert_func>>,
                  std::optional<char>, std::optional<char>)>(&oop::stats::load),
          "Load a CSV into a new DataFrame",
          py::arg("filepath"),
          py::arg("header") = std::nullopt,
          py::arg("columns") = std::nullopt,
          py::arg("col_types") = std::nullopt,
          py::arg("newline_delimiter") = std::nullopt,
          py::arg("column_delimiter") = std::nullopt
          );

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}