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
    typedef std::variant<arma::Col<int>,
            arma::Col<long int>,
            arma::Col<long long int>,
            arma::Col<float>,
            arma::Col<double>,
            arma::Col<unsigned int>,
            arma::Col<unsigned long int>,
            arma::Col<unsigned long long int>,
            arma::Col<std::complex<double>>,
            arma::Col<std::complex<float>>> sup_col_types;

    // All supported column internal value types.
    typedef std::variant<int, long int, long long int, float, double,
            unsigned int, unsigned long int, unsigned long long int, std::complex<double>,
            std::complex<float>> sup_single_types;

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

        // Check that an index is within bounds an throw an error if not.
        inline void check_col_bounds(arma::uword idx) const;

        inline void check_row_bounds(arma::uword idx) const;

    public:
        inline explicit DataFrame(
                const std::vector<std::vector<sup_single_types>> &data,
                std::optional<std::vector<std::string>> labels = std::nullopt);

        DataFrame() = default;

        // A const view of all columns in the DataFrame.
        const std::vector<sup_col_types> &
        get_columns() const { return columns; }

        // Get the column labels.
        [[nodiscard]] inline auto column_labels() const {
            return _column_labels;
        };

        // Column label setter. The amount of provided tables must match the
        // amount of initialized columns.
        inline void set_column_labels(const std::vector<std::string> &labels);

        // Cat map getter
        [[nodiscard]] inline cat_map_t &get_map(
                const std::variant<arma::uword, std::string> idx);

        // Cat map setter.
        inline void set_map(const arma::uword idx, const cat_map_t &map) {
            this->check_col_bounds(idx);
            this->cat_map[idx] = map;
        };

        // Get all CatMaps in the DataFrame
        [[nodiscard]] inline const std::unordered_map<arma::uword, cat_map_t> &
        get_all_maps() const { return this->cat_map; };

        inline void set_all_maps(
                std::unordered_map<arma::uword, cat_map_t> &maps) { this->cat_map = maps; };

        // Shape of the matrix.
        [[nodiscard]] inline std::pair<arma::uword, arma::uword> shape() const;

        // Function that searches the labels for a specific label.
        inline arma::uword find_label(const std::string &label) const;

        // Indexing
        inline sup_col_types &operator[](std::size_t idx);

        inline const sup_col_types &operator[](std::size_t idx) const;

        // Indexing by column label
        inline sup_col_types &operator()(const std::string &label);

        inline const sup_col_types &operator()(const std::string &label) const;

        // Set a column with checks, much better than doing df[x] = col.
        inline void set_column(sup_col_types &col, arma::uword &idx);

        // Append a row to the bottom of the dataframe.
        inline void
        append_row(const std::vector<sup_single_types> &append_data);

        inline void insert_row(const std::vector<sup_single_types> &append_data,
                               const arma::uword &idx);

        inline void
        insert_column(const sup_col_types &col, const arma::uword &idx,
                      const std::optional<std::string> &label = std::nullopt);

        inline void append_column(sup_col_types &col,
                                  const std::optional<std::string> &label = std::nullopt) {
            std::cout << std::endl;
            insert_column(col, shape().second, label);
        };

        // Print a summary of the dataframe.
        inline void summarize();
    };

    // A functor for inserting a row into an armadillo column vector. For
    // use with std::visit.
    class InsertRow {
        arma::uword idx;
        bool dry;
    public:
        inline explicit InsertRow(arma::uword idx, bool dry = true);

        template<template<typename B> typename A, typename B>
        void operator()(A<B> &row, const B &item);
    };

    // A functor for appending a column into the DataFrame.
    class AppendColumn {
        DataFrame *parent;
    public:
        explicit AppendColumn(DataFrame *parent) : parent{parent} {}

        template<typename B>
        void operator()(const B &item);
    };

    // Implementation

    inline DataFrame::DataFrame(
            const std::vector<std::vector<sup_single_types>> &data,
            std::optional<std::vector<std::string>> labels) {
        for (const auto &i: data) {
            this->append_row(i);
        }
        if (labels) { this->set_column_labels(*labels); }
    }

    template<typename B>
    void AppendColumn::operator()(const B &item) {
        arma::Col<B> col{1};
        col(0) = item;
        parent->columns.push_back(col);
    }

    inline InsertRow::InsertRow(arma::uword idx, bool dry) :
            idx{idx}, dry{dry} {}

    template<template<typename B> typename A, typename B>
    void InsertRow::operator()(A<B> &row, const B &item) {
        if (!this->dry) {
            arma::Row<B> to_insert{1};
            to_insert(0, 0) = item;
            row.insert_rows(this->idx, to_insert);
        }
    }

    inline std::pair<arma::uword, arma::uword> DataFrame::shape() const {
        if (this->columns.empty()) { return {0, 0}; }
        arma::uword rows;
        arma::uword cols;
        rows = std::visit(
                [](auto &col) { return col.n_rows; },
                this->columns[0]);
        cols = this->columns.size();
        return {rows, cols};
    }

    inline void DataFrame::insert_row(
            const std::vector<sup_single_types> &append_data,
            const arma::uword &idx) {
        this->check_row_bounds(idx);
        // When there are no columns present they get initialized.
        if (this->shape().second == 0) {
            for (const auto &i: append_data) {
                std::visit(AppendColumn(this), i);
            }
            return;
        } else if (this->shape().second != append_data.size() and
                   this->shape().second != 0) {
            throw std::length_error("The provided row has an incorrect length");
        }

        // When InsertRow is invalid this function gets called. This should
        // only happen when the provided item does not match the type of the
        // column.
        static auto base = [](auto, auto) {
            throw std::invalid_argument(
                    "Some provided type did not match with the column type when "
                    "appending a row");
        };

        // Check that all types are correct before inserting anything.
        for (std::size_t i = 0; i < this->shape().second; ++i) {
            std::visit(overloaded{InsertRow(idx), base},
                       (*this)[i], append_data[i]);
        }
        // Now we insert.
        for (std::size_t i = 0; i < this->shape().second; ++i) {
            std::visit(overloaded{InsertRow(idx, false), base},
                       (*this)[i], append_data[i]);
        }
    }

    inline void DataFrame::append_row(
            std::vector<sup_single_types> const &append_data) {
        this->insert_row(append_data, this->shape().first);
    }

    inline void
    DataFrame::insert_column(const sup_col_types &col, const arma::uword &idx,
                             const std::optional<std::string> &label) {
        // Get the number of rows in the provided column
        arma::uword n_rows;
        n_rows = std::visit([](auto c) { return c.n_rows; }, col);
        // Check if the number of rows matches the rest of the DataFrame.
        if (n_rows != this->shape().first and this->shape().second != 0) {
            throw std::invalid_argument(
                    "Cannot append a column with an incorrect amount of rows"
            );
        }
        if (idx > this->shape().second) {
            throw std::out_of_range(
                    "Cannot append a column at an invalid index."
            );
        }
        // Add the label if it exists.
        if (label.has_value()) {
            auto current_labs{this->column_labels()};
            if (!current_labs.has_value() and this->shape().second != 0) {
                throw std::invalid_argument(
                        "Requested a label for a new column but the current "
                        "dataframe does not have labels. Please set all the "
                        "labels at once with the label setter.");
            }
            auto it = (*(this->_column_labels)).begin();
            for (arma::uword i = 0; i < idx; ++i) { it++; }
            (*(this->_column_labels)).insert(it, *label);
        }
        auto it = this->columns.begin();
        std::advance(it, idx);
        this->columns.insert(it, col);
    }

    inline void DataFrame::summarize() {
        auto col_labels = this->column_labels();
        if (col_labels.has_value()) {
            for (const auto &i: *col_labels) {
                std::cout << i << ", ";
            }
            std::cout << std::endl;
        }
        arma::uword default_rows{5};
        arma::uword no_rows{std::min(this->shape().first, default_rows)};
        for (arma::uword i = 0; i < no_rows; ++i) {
            for (arma::uword j = 0; j < this->shape().second; ++j) {
                std::visit([i](auto &col) { std::cout << col[i] << " "; },
                           (*this)[j]);
            }
            std::cout << std::endl;
        }
        auto c_shape{this->shape()};
        std::cout << "Dataset shape: (" << c_shape.second << ", " <<
                  c_shape.first << ")" << std::endl;
    }

    inline void
    DataFrame::set_column_labels(const std::vector<std::string> &labels) {
        if (this->shape().second != labels.size()) {
            throw std::length_error("There is an incorrect number of provided "
                                    "column labels.");
        }
        this->_column_labels = labels;
    }

    inline arma::uword DataFrame::find_label(const std::string &label) const {
        auto labels{this->column_labels()};
        if (!labels) { throw std::out_of_range("DataFrame has no labels"); }
        auto it = std::find((*labels).begin(), (*labels).end(), label);
        if (it == (*labels).end()) {
            throw std::out_of_range("Provided label not found in DataFrame");
        }
        auto idx = std::distance((*labels).begin(), it);
        return idx;
    }

    inline sup_col_types &DataFrame::operator()(const std::string &label) {
        auto idx{this->find_label(label)};
        return (*this)[idx];
    }

    inline const sup_col_types &
    DataFrame::operator()(const std::string &label) const {
        auto idx{this->find_label(label)};
        return (*this)[idx];
    }

    inline void DataFrame::set_column(sup_col_types &col, arma::uword &idx) {
        this->check_row_bounds(idx);
        auto n_rows = std::visit([](auto &c) { return c.n_rows; }, col);
        if (n_rows > this->shape().first) {
            throw std::invalid_argument("The provided column has an incorrect "
                                        "number of rows!");
        }
        (*this)[idx] = col;
    }

    sup_col_types &DataFrame::operator[](std::size_t idx) {
        this->check_col_bounds(idx);
        return this->columns[idx];
    }

    const sup_col_types &DataFrame::operator[](std::size_t idx) const {
        this->check_col_bounds(idx);
        return this->columns[idx];
    }

    inline void DataFrame::check_col_bounds(const arma::uword idx) const {
        if (idx >= this->shape().second) {
            throw std::out_of_range("The provided index is larger than the "
                                    "amount of columns in the DataFrame!");
        }
    }

    inline void DataFrame::check_row_bounds(const arma::uword idx) const {
        if (idx > this->shape().first) {
            throw std::out_of_range("Index out of bounds when inserting row.");
        }
    }

    cat_map_t& DataFrame::get_map(const std::variant<arma::uword,
            std::string> idx) {
        arma::uword col_idx{std::visit(overloaded{
                [](const arma::uword &idx) { return idx; },
                [this](const std::string &lab) {
                    return this->find_label(lab);
                }}, idx)};
        cat_map_t& map{this->cat_map[col_idx]};
        return map;
    }
}

#endif //EXAMPLES_DATAFRAME_HPP
