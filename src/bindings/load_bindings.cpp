//
// Created by uki on 1/4/24.
//
#include "load_bindings.hpp"
#include <carma>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace oop::bindings {
    void load_bindings(py::module_ &m) {
        m.def("load",
              static_cast<std::vector<std::string> (*)
                      (const std::string&,
                       oop::stats::DataFrame&,
                       std::optional<bool>,
                       const std::optional<std::vector<int>>&,
                       std::optional<std::vector<oop::stats::convert_func>>,
                       std::optional<char>,
                       std::optional<char>)>
              (&oop::stats::load),
              "Load a CSV into a DataFrame",
              py::arg("filepath"),
              py::arg("dataframe"),
              py::arg("header") = std::nullopt,
              py::arg("columns") = std::nullopt,
              py::arg("col_types") = std::nullopt,
              py::arg("newline_delimiter") = std::nullopt,
              py::arg("column_delimiter") = std::nullopt
        );
        m.def("load",
              static_cast<std::pair<std::vector<std::string>,
                      oop::stats::DataFrame> (*)
                      (const std::string&,
                       std::optional<bool>,
                       const std::optional<std::vector<int>>&,
                       std::optional<std::vector<oop::stats::convert_func>>,
                       std::optional<char>, std::optional<char>)>
              (&oop::stats::load),
              "Load a CSV into a new DataFrame",
              py::arg("filepath"),
              py::arg("header") = std::nullopt,
              py::arg("columns") = std::nullopt,
              py::arg("col_types") = std::nullopt,
              py::arg("newline_delimiter") = std::nullopt,
              py::arg("column_delimiter") = std::nullopt
        );
    }
}
