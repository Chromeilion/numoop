//
// Created by uki on 12/31/23.
//
#include "dataframe_bindings.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::stats::bindings {
    void df_init(py::class_<oop::stats::DataFrame> &m) {
        m.def(py::init<>());
        m.def(py::init<std::vector<std::vector<oop::stats::sup_single_types>> &,
                      std::optional<std::vector<std::string>>>(),
              py::arg("data"),
              py::arg("labels") = std::nullopt,
              R"pbdoc(
Parameters
----------
data : list or list[list], optional
labels : list[str], optional
)pbdoc");
    }

}
