//
// Created by uki on 1/6/24.
//
#include "dataframe_bindings.hpp"
#include "df_helpers.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py=pybind11;
namespace oop::bindings {
    void df_pickle(py::class_<oop::stats::DataFrame> &m) {
        m.def(py::pickle(
                [](const oop::stats::DataFrame &self) {
                    auto cols = self.get_columns();
                    std::vector<sup_arr_types> conv_cols;
                    for (auto &i : cols) {
                        auto conv_col = convert_col(i);
                        conv_cols.push_back(conv_col);
                    }
                    return py::make_tuple(conv_cols,
                                          self.get_all_maps(),
                                          self.column_labels());},
                [](py::tuple &t) {
                    auto self = new oop::stats::DataFrame();
                    auto cols = t[0].cast<std::vector<sup_arr_types>>();
                    auto maps = t[1].cast<std::unordered_map<
                            arma::uword, oop::stats::cat_map_t>>();
                    auto labels = t[2].cast<std::vector<std::string>>();
                    for (auto &i: cols) {
                        auto converted_col = transfer_col_ownership(i);
                        self->append_column(converted_col);}
                    self->set_column_labels(labels);
                    self->set_all_maps(maps);
                    return self;})
        );
    }
}
