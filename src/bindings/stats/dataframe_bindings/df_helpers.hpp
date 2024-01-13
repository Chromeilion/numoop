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
    // Functor for creating a const numpy view into an arma array.
    class ToNumpyView {
    public:
        template<typename T>
        inline sup_arr_types operator()(const T &col) const {
            const auto view = carma::to_numpy_view<T>(col);
            const sup_arr_types conv{view};
            return conv;
        }
    };
    // Functor for getting an element from a DataFrame with an int or str index.
    class GetIdx {
        const oop::stats::DataFrame& self;
    public:
        inline explicit GetIdx(const oop::stats::DataFrame& self_) : self{self_} {};
        inline const oop::stats::sup_col_types& operator()(const unsigned &idx)
        const {return self[idx];}
        inline const oop::stats::sup_col_types& operator()(const std::string &lab)
        const {return self(lab);}
    };
}

#endif //NUMOOP_DF_HELPERS_HPP
