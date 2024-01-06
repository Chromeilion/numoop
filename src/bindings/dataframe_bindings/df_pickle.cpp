//
// Created by uki on 1/6/24.
//
#include "dataframe_bindings.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py=pybind11;
namespace oop::bindings {
    void df_pickle(py::class_<oop::stats::DataFrame> &m) {
        m.def(py::pickle(
                [](const oop::stats::DataFrame &self) {
                    return py::make_tuple(self.get_columns(),
                                          self.get_all_maps(),
                                          self.column_labels());},
                [](py::tuple &t) {
                    auto self = new oop::stats::DataFrame();
                    auto cols = t[0].cast<std::vector<oop::stats::sup_col_types>>();
                    auto maps = t[1].cast<std::unordered_map<
                            arma::uword, oop::stats::cat_map_t>>();
                    auto labels = t[2].cast<std::vector<std::string>>();
                    for (auto &i: cols) {
                        self->append_column(i);}
                    self->set_column_labels(labels);
                    self->set_all_maps(maps);
                    return self;
                })
        );
    }
}
