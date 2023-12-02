//
// Created by uki on 11/30/23.
//

#ifndef EXAMPLES_DATAFRAME_HPP
#define EXAMPLES_DATAFRAME_HPP
#include <utility>
#include <vector>
#include <string>
#include <variant>
#include <armadillo>
#include "misc.hpp"
#include <optional>
#include <cassert>

namespace oop::stats {
    // All supported column types.
    typedef std::variant <arma::dcolvec, arma::cx_dcolvec, arma::cx_fcolvec,
            arma::ucolvec, arma::icolvec> sup_col_types;

    // All supported column internal value types.
    typedef std::variant<double, arma::cx_double, arma::cx_float,
            arma::uword, arma::sword> sup_single_types;

    // DataFrame class. Similar in spirit to a Pandas DataFrame. Groups together
    // multiple Armadillo Col classes of (potentially) different types.
    class DataFrame {
    private:
        // A functor for inserting a row into an armadillo column vector. For
        // use with std::visit.
        class InsertRow {
        public:
            template<template<typename B> typename A, typename B>
            void operator()(A<B> &row, const B &item);
        };

        // Each column in the dataframe is represented by an armadillo Col
        // object which can hold most types minus strings.
        std::vector<sup_col_types> columns;
        // The column types as strings. Not used directly but may be useful to
        // the end user.
        std::vector<std::string> _column_types;

        // Column labels, usually correspond to a CSV header.
        std::optional<std::vector<std::string>> _column_labels;
    public:
        explicit DataFrame(
                std::optional<std::vector<std::string>> column_labels = std::nullopt
                        ) : _column_labels{std::move(column_labels)} {}

        // Column types getter.
        [[nodiscard]] const std::vector<std::string>& column_types() const {
            return _column_types;};

        // Get the column labels.
        [[nodiscard]] auto column_labels() const {
            return _column_labels;};

        // Column label setter. Does not check for the correct number of labels.
        void set_column_labels(const std::optional<std::vector<std::string>> &labels) {
            this->_column_labels = labels;}

        // Shape of the matrix.
        [[nodiscard]] std::pair<arma::uword, arma::uword> shape() const;

        // Indexing
        sup_col_types &operator[](std::size_t idx) { return columns[idx]; }
        const sup_col_types &operator[](std::size_t idx) const { return columns[idx]; }

        // Append a row to the bottom of the dataframe.
        void append_row(const std::vector<sup_single_types>& append_data);

        void insert_column(sup_col_types &col, const arma::uword &idx);
        void append_column(sup_col_types &col) { insert_column(col, shape().second);};
    };

    // Implementation

    template<template<typename B> typename A, typename B>
    void DataFrame::InsertRow::operator()(A<B> &row, const B &item) {
        arma::Row <B> to_insert{1, 1};
        to_insert(0, 0) = item;
        row.insert_rows(row.n_rows - 1, to_insert);
    }

    std::pair<arma::uword, arma::uword> DataFrame::shape() const {
        arma::uword rows;
        arma::uword cols;
        rows = std::visit(
                [](auto &col){return col.n_rows;},
                (*this)[0]);
        cols = this->columns.size();
        return {rows, cols};
    }

    void DataFrame::append_row(std::vector<sup_single_types> const &append_data) {
        // When InsertRow is invalid this function gets called. This should
        // only happen when the provided item does not match the type of the
        // column.
        auto base = [](auto, auto){throw std::runtime_error(
                "Some provided type did not match with the column type when "
                "appending a row");};

        for (std::size_t i = 0; i < this->shape().second; ++i) {
            std::visit(overloaded{DataFrame::InsertRow(), base},
                       (*this)[i], append_data[i]);
        }
    }

    void DataFrame::insert_column(sup_col_types &col, const arma::uword &idx) {
        std::vector<sup_col_types>::iterator it;
        it = this->columns.begin();
        advance(it, idx);
        this->columns.insert(it, col);
    }
}

#endif //EXAMPLES_DATAFRAME_HPP
