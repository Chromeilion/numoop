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
#include <optional>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "misc.hpp"

namespace oop::stats {
    // All supported column types.
    typedef std::variant <arma::dcolvec, arma::cx_dcolvec, arma::cx_fcolvec,
            arma::ucolvec, arma::icolvec> sup_col_types;

    // All supported column internal value types.
    typedef std::variant<double, arma::cx_double, arma::cx_float,
            arma::uword, arma::sword> sup_single_types;

    // Map of ints to string categories
    typedef std::unordered_map<arma::uword, std::string> cat_map_t;

    class AppendColumn;

    // DataFrame class. Similar in spirit to a Pandas DataFrame. Groups together
    // multiple Armadillo Col classes of (potentially) different types.
    class DataFrame {
        friend AppendColumn;
    private:
        // Each column in the dataframe is represented by an armadillo Col
        // object which can hold most types minus strings.
        std::vector<sup_col_types> columns;

        // Map that stores for each column what int represents what string.
        std::unordered_map<arma::uword, cat_map_t> cat_map;

        // Column labels, usually correspond to a CSV header.
        std::optional<std::vector<std::string>> _column_labels;

        // Function that searches the labels for a specific label.
        auto find_label(const std::string &label) const;
    public:
        // Get the column labels.
        [[nodiscard]] auto column_labels() const {
            return _column_labels;};

        // Cat map getter
        [[nodiscard]] cat_map_t& get_map(const arma::uword idx) {
            return this->cat_map[idx];};

        // Cat map setter.
        void set_map(const arma::uword idx, const cat_map_t map) {
            this->cat_map[idx] = map;};

        // Column label setter. The amount of provided tables must match the
        // amount of initialized columns.
        void set_column_labels(const std::vector<std::string> &labels);

        // Shape of the matrix.
        [[nodiscard]] std::pair<arma::uword, arma::uword> shape() const;

        // Indexing
        sup_col_types &operator[](std::size_t idx) { return columns[idx]; }
        const sup_col_types &operator[](std::size_t idx) const { return columns[idx]; }

        // Indexing by column label
        sup_col_types &operator()(const std::string& label);
        const sup_col_types &operator()(const std::string& label) const;

        // Append a row to the bottom of the dataframe.
        void append_row(const std::vector<sup_single_types>& append_data);

        void insert_column(sup_col_types &col, const arma::uword &idx,
                           const std::optional<std::string> &label);
        void append_column(sup_col_types col,
                           const std::optional<std::string> &label) {
            insert_column(col, shape().second, label);};

        // Print a summary of the dataframe.
        void summarize();
    };

    // A functor for inserting a row into an armadillo column vector. For
    // use with std::visit.
    class InsertRow {
    public:
        template<template<typename B> typename A, typename B>
        void operator()(A<B> &row, const B &item);
    };

    // A functor for appending a column into the DataFrame.
    class AppendColumn {
        DataFrame* parent;
    public:
        explicit AppendColumn(DataFrame* parent) : parent{parent} {}
        template<typename B>
        void operator()(const B &item);
    };

    // Implementation

    template<typename B>
    void AppendColumn::operator()(const B &item) {
        arma::Col<B> col{1};
        col(0) = item;
        parent->columns.push_back(col);
    }

    template<template<typename B> typename A, typename B>
    void InsertRow::operator()(A<B> &row, const B &item) {
        arma::Row <B> to_insert{1};
        to_insert(0, 0) = item;
        row.insert_rows(row.n_rows, to_insert);
    }

    std::pair<arma::uword, arma::uword> DataFrame::shape() const {
        if (this->columns.empty()) {return {0, 0};}
        arma::uword rows;
        arma::uword cols;
        rows = std::visit(
                [](auto &col){return col.n_rows;},
                (*this)[0]);
        cols = this->columns.size();
        return {rows, cols};
    }

    void DataFrame::append_row(std::vector<sup_single_types> const &append_data) {
        // When there are no columns present they get initialized.
        if (this->shape().second == 0) {
            for (const auto & i : append_data) {
                std::visit(AppendColumn(this), i);
            }
            return;
        }
        if (this->shape().second != append_data.size() and this->shape().second != 0) {
            throw std::length_error("The provided row has an incorrect length");
        }

        // When InsertRow is invalid this function gets called. This should
        // only happen when the provided item does not match the type of the
        // column.
        static auto base = [](auto, auto){
            throw std::runtime_error(
                "Some provided type did not match with the column type when "
                "appending a row");};

        for (std::size_t i = 0; i < this->shape().second; ++i) {
            std::visit(overloaded{InsertRow(), base},
                       (*this)[i], append_data[i]);
        }
    }

    void DataFrame::insert_column(sup_col_types &col, const arma::uword &idx,
                                  const std::optional<std::string> &label) {
        if (label.has_value()) {
            auto current_labs{this->column_labels()};
            if (!current_labs.has_value()) {
                throw std::runtime_error("Requested a label for a new column but the "
                                         "current dataframe does not have labels.");}
            auto it = (*this->_column_labels).begin();
            for (arma::uword i=0; i<idx; ++i) {it++;}
            (*this->_column_labels).insert(it, *label);
        }
        std::vector<sup_col_types>::iterator it;
        it = this->columns.begin();
        advance(it, idx);
        this->columns.insert(it, col);
    }

    void DataFrame::summarize() {
        auto col_labels = this->column_labels();
        if (col_labels.has_value()) {
            for (const auto &i : *col_labels) {
                std::cout << i << ", ";
            }
            std::cout << std::endl;
        }
        arma::uword default_rows{5};
        arma::uword no_rows{std::min(this->shape().first, default_rows)};
        for (arma::uword i = 0; i<no_rows; ++i) {
            for(arma::uword j = 0; j<this->shape().second; ++j) {
                std::visit([i](auto &col){std::cout << col[i] << " ";},
                           (*this)[j]);
            }
            std::cout << std::endl;
        }
        auto c_shape{this->shape()};
        std::cout << "Dataset shape: (" << c_shape.second << ", " <<
        c_shape.first << ")" << std::endl;
    }

    void DataFrame::set_column_labels(const std::vector<std::string> &labels) {
        if (this->shape().second != labels.size()) {
            throw std::length_error("There is an incorrect number of provided "
                                    "column labels.");
        }
        this->_column_labels = labels;
    }

    auto DataFrame::find_label(const std::string &label) const {
        auto labels{this->column_labels()};
        if (!labels) {throw std::out_of_range("DataFrame has no labels");}
        auto it = std::find((*labels).begin(), (*labels).end(), label);
        if (it == (*labels).end()) {
            throw std::out_of_range("Provided label not found in DataFrame");
        }
        auto idx = std::distance((*labels).begin(), it);
        return idx;
    }
    sup_col_types &DataFrame::operator()(const std::string& label) {
        auto idx{this->find_label(label)};
        return (*this)[idx];
    }
    const sup_col_types &DataFrame::operator()(const std::string& label) const {
        auto idx{this->find_label(label)};
        return (*this)[idx];
    }
}

#endif //EXAMPLES_DATAFRAME_HPP
