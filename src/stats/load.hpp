//
// Created by uki on 11/30/23.
//

#ifndef EXAMPLES_LOAD_HPP
#define EXAMPLES_LOAD_HPP
#include <armadillo>
#include <string>
#include <fstream>
#include <ios>
#include <optional>
#include "dataframe.hpp"
#include "parse.hpp"

namespace oop::stats {
    // Split a string wherever some char is present
    inline std::vector<std::string> split_line(const std::string &line, const char &delimiter);

    // Read a line from a file into a vector of strings
    inline bool read_line(
            std::fstream &file,
            std::vector<std::string>& line,
            const char &newline_delimiter,
            const char &column_delimiter,
            const std::optional<std::vector<int>>& columns = std::nullopt);

    // Load a CSV file into a DataFrame.
    inline std::vector<std::string> load(
            const std::string& filepath,
            oop::stats::DataFrame& matr,
            std::optional<bool> header = std::nullopt,
            const std::optional<std::vector<int>>& columns = std::nullopt,
            std::optional<std::vector<convert_func>> col_types = std::nullopt,
            std::optional<char> newline_delimiter = std::nullopt,
            std::optional<char> column_delimiter = std::nullopt);
    // Load into a new DataFrame. Not ideal because it involves an extra copy on
    // return, but it's more convenient.
    inline std::pair<std::vector<std::string>, DataFrame> load(
            const std::string& filepath,
            std::optional<bool> header = std::nullopt,
            const std::optional<std::vector<int>>& columns = std::nullopt,
            std::optional<std::vector<convert_func>> col_types = std::nullopt,
            std::optional<char> newline_delimiter = std::nullopt,
            std::optional<char> column_delimiter = std::nullopt);

    // Implementation

    inline std::vector<std::string> split_line(const std::string &line, const char &delimiter) {
        std::vector<std::string> splits;
        std::string word;
        std::stringstream str(line);
        while (getline(str, word, delimiter)) {
            splits.push_back(word);
        }
        return splits;
    }

    inline bool read_line(
            std::fstream& file,
            std::vector<std::string>& line,
            const char& newline_delimiter,
            const char& column_delimiter,
            const std::optional<std::vector<int>>& columns) {
        std::string full_line;
        std::vector<std::string> temp_line;
        if (getline(file, full_line, newline_delimiter)) {
            // Remove any possible trailing \r characters.
            full_line.erase(std::remove(full_line.begin(),
                                        full_line.end(), '\r' ),
                            full_line.end());
            
            temp_line = split_line(full_line, column_delimiter);
            line.clear();
            if (columns.has_value()) {
                for (auto& col : *columns) {
                    line.push_back(temp_line[col]);
                }
            }
            else { line = temp_line; }
            return true;
        }
        return false;
    }

    inline std::vector<std::string> load(
            const std::string& filepath,
            oop::stats::DataFrame& matr,
            std::optional<bool> header,
            const std::optional<std::vector<int>>& columns,
            std::optional<std::vector<convert_func>> col_types,
            std::optional<char> newline_delimiter,
            std::optional<char> column_delimiter) {
        if (!newline_delimiter) {newline_delimiter = '\n';}
        if (!column_delimiter) {column_delimiter = ',';}

        std::fstream file(filepath, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error(
                    "Error trying to read CSV file");
        }

        // Strings where each line and word will be stored.
        std::string word;
        std::vector<std::string> line;

        // Store auto-detected types in a vector of strings.
        std::vector<std::string> col_str;

        // Read the first line if there is a header present.
        std::vector<std::string> full_header;
        if (header.has_value()) {
            if (*header) {
                read_line(file, full_header, *newline_delimiter,
                          *column_delimiter, columns);
            }
        }
        // The first line of data is read outside the loop because some
        // extra operations such as type inference have to be performed.
        if (!read_line(file, line, *newline_delimiter, *column_delimiter,
                       columns)) {return col_str;}

        // Categorical variable maps get stored in a mapfor later use.
        std::vector<arma::uword> cat_vars;
        if (!col_types.has_value()) {
            col_types = oop::stats::infer_types(line, col_str, cat_vars);
        }

        std::vector<oop::stats::sup_single_types> row = convert_strings(
                line, *col_types, columns);
        matr.append_row(row);

        // Add the header, keeping in mind that the user may not want all
        // columns.
        if (!full_header.empty()) {
            if (columns.has_value()) {
                std::vector<std::string> new_header;
                new_header.reserve(full_header.size());
        for (const auto& str: full_header) {new_header.push_back(str);}
                matr.set_column_labels(new_header);
            } else {matr.set_column_labels(full_header);}
        }
        // Append the rest of the CSV file, assuming constant types.
        while (read_line(file, line, *newline_delimiter, *column_delimiter,
                         columns)) {
            matr.append_row(convert_strings(line, *col_types, columns));
        }

        // Add the categorical mappings if there are any.
        for (const auto idx:  cat_vars) {
            auto *cat_map = (*col_types)[idx].target<CatMap>();
            matr.set_map(idx, cat_map->get_swapped_map());
        }
        return col_str;
    }
    inline std::pair<std::vector<std::string>, DataFrame> load(
            const std::string& filepath,
            std::optional<bool> header,
            const std::optional<std::vector<int>>& columns,
            std::optional<std::vector<convert_func>> col_types,
            std::optional<char> newline_delimiter,
            std::optional<char> column_delimiter) {
        DataFrame new_df;
        std::vector<std::string> types = load(
                filepath, new_df, header, columns, col_types,
                newline_delimiter, column_delimiter);
        return {types, new_df};
    }
}

#endif //EXAMPLES_LOAD_HPP
