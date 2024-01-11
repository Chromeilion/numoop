//
// Created by uki on 1/6/24.
//

#ifndef NUMOOP_DF_HELPERS_HPP
#define NUMOOP_DF_HELPERS_HPP
#include <stats/stats.hpp>
#include "dataframe_bindings.hpp"

namespace oop::stats::bindings {
    class ConvertArray;
    sup_arr_types convert_col(oop::stats::sup_col_types &col);
    oop::stats::sup_col_types transfer_col_ownership(sup_arr_types &col);
}

#endif //NUMOOP_DF_HELPERS_HPP
