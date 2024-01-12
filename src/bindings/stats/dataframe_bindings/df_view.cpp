//
// Created by uki on 1/6/24.
//
#include "dataframe_bindings.hpp"
#include <variant>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <carma>

namespace py=pybind11;
namespace oop::stats::bindings {
    sup_arr_types view_wrapper(const oop::stats::DataFrame &self,
                               const std::variant<unsigned, std::string> &idx) {
        const auto &col = std::visit(overloaded{
            [&self](const unsigned &index){return self[index];},
            [&self](const std::string &lab){return self(lab);}
            }, idx);
        auto to_view_wrap = [](auto &c)
                {return sup_arr_types{carma::to_numpy_view(c)};};
        return std::visit(to_view_wrap, col);
    }

    void df_view(py::class_<oop::stats::DataFrame> &m) {
        m.def("view", view_wrapper,
              py::arg("idx"),
              R"pbdoc(
Get a view into a column. This is much faster than indexing the dataframe
because the column memory is not copied. This does mean however that the
returned Numpy array is read-only.

Parameters
----------
idx : unsigned int or string

Returns
-------
col : np.typing.NDArray
    A read-only numpy array.
)pbdoc");
    }
}
