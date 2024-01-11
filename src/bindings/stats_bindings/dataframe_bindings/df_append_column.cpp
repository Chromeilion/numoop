//
// Created by uki on 1/4/24.
//
#include "dataframe_bindings.hpp"
#include "df_helpers.hpp"
#include <stats/stats.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace oop::bindings {
    void append_column_wrapper(
            oop::stats::DataFrame &self,
            sup_arr_types &col,
            const std::optional<std::string> &label = std::nullopt) {
        auto conv_col = transfer_col_ownership(col);
        self.append_column(conv_col, label);
    }
    void df_append_column(py::class_<oop::stats::DataFrame> &m) {
        m.def("append_column", &append_column_wrapper,
              py::arg("col").noconvert(true),
              py::arg("label")=std::nullopt,
              R"pbdoc(
Append a column to the DataFrame. Must have a correct amount of
rows.

Parameters
----------
col : numpy.typing.NDArray
    Must be a column vector i.e. shape=(x, 1)
label : Optional[str]
)pbdoc");
    }
}
