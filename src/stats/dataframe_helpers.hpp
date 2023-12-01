//
// Created by uki on 12/1/23.
//

#ifndef EXAMPLES_DATAFRAME_HELPERS_HPP
#define EXAMPLES_DATAFRAME_HELPERS_HPP
#include <variant>
#include <armadillo>

namespace oop::stats {
    // For overloading inside a std::visit call. Taken from the documentation:
    // https://en.cppreference.com/w/cpp/utility/variant/visit
    template<class... Ts>
    struct overloaded : Ts ... {
        using Ts::operator()...;
    };
    template<class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    // A function for inserting a row into a column vector. For use with
    // std::visit.
    class InsertRow {
    public:
        template<template<typename B> typename A, typename B>
        auto operator()(A<B> &row, B &item) {
            arma::Row <B> to_insert{1, 1};
            to_insert(0, 0) = item;
            row.insert_rows(row.n_rows - 1, to_insert);
        }
    };
}
#endif //EXAMPLES_DATAFRAME_HELPERS_HPP
