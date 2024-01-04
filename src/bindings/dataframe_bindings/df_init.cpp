//
// Created by uki on 12/31/23.
//
#include "dataframe_bindings.hpp"

namespace py = pybind11;

namespace oop::bindings {
    void df_init(py::class_<oop::stats::DataFrame> &m) {
        m.def(py::init<>());
        m.def(py::init<std::vector<std::vector<oop::stats::sup_single_types>> &,
                      std::optional<std::vector<std::string>>>(),
              py::arg("data"),
              py::arg("labels") = std::nullopt);
    }

}
