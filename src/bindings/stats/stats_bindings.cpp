//
// Created by uki on 1/11/24.
//

#include "stats_bindings.hpp"
#include "load_bindings.hpp"
#include "dataframe_bindings/dataframe_bindings.hpp"


namespace oop::stats::bindings {
    void stats_bindings(pybind11::module_ &m) {
        load_bindings(m);
        dataframe_bindings(m);
    }
}
