//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/pybind11.h>
#include <stats/stats.hpp>

namespace py = pybind11;
namespace oop::bindings {
    void df_summarize(py::class_<oop::stats::DataFrame> &m) {
        m.def("summarize",
              &oop::stats::DataFrame::summarize,
              R"pbdoc(
Print a summary of the DataFrame.
)pbdoc");
    }
}
