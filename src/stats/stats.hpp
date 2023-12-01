//
// Created by chromeilion on 11/25/23.
//

#ifndef NUMOOP_STATS_HPP
#define NUMOOP_STATS_HPP
#include <armadillo>
#include <vector>
#include <variant>
#include <string>
#include <map>
#include <any>
#include <optional>
#include "dataframe.hpp"

namespace oop::stats {
    // A union storing either the names of the column/s to load or the index/s
    union Columns;

    // Load a CSV file into an Armadillo matrix. All values will be converted to
    // type T. Categorical values are first converted to ints and then to type T.
    // You can optionally specify what columns you'd like, either with the column
    // name (present in the header) or column index (starting at 0)
    template<typename T>
    oop::stats::DataFrame &load(std::string &filepath,
               oop::stats::Columns &columns,
               std::optional<std::vector<std::string>> col_types,
               bool header = true,
               char newline_delimiter = '\n',
               char column_delimiter = ',');
}

#include "_load.hpp"
#endif //NUMOOP_STATS_HPP
