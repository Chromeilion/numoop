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
    std::vector<std::string> split_line(const std::string &line, const char &delimiter);

    // Read a line from a file into a vector of strings
    bool read_line(
            std::fstream &file,
            std::vector<std::string>& line,
            const char &newline_delimiter,
            const char &column_delimiter,
            const std::optional<std::vector<int>>& columns = std::nullopt);

    // Load a CSV file into a DataFrame.
    void load(
            std::string& filepath,
            oop::stats::DataFrame& matr,
            std::optional<bool> header = std::nullopt,
            const std::optional<std::vector<int>>& columns = std::nullopt,
            std::optional<std::vector<convert_func>> col_types = std::nullopt,
            char newline_delimiter = '\n',
            char column_delimiter = ',');

    // Implementation

    std::vector<std::string> split_line(const std::string &line, const char &delimiter) {
        std::vector<std::string> splits;
        std::string word;
        std::stringstream str(line);
        while (getline(str, word, delimiter)) {
            splits.push_back(word);
        }
        return splits;
    }

    bool read_line(
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

    void load(
            std::string& filepath,
            oop::stats::DataFrame& matr,
            std::optional<bool> header,
            const std::optional<std::vector<int>>& columns,
            std::optional<std::vector<convert_func>> col_types,
            char newline_delimiter,
            char column_delimiter) {
        std::fstream file(filepath, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error(
                    "Error trying to read CSV file");
        }

        // Strings where each line and word will be stored.
        std::string word;
        std::vector<std::string> line;

        // Read the first line if there is a header present.
        std::vector<std::string> full_header;
        if (header.has_value()) {
            if (*header) {
                read_line(file, full_header, newline_delimiter,
                          column_delimiter, columns);
            }
        }
        // The first line of data is read outside the loop because some
        // extra operations such as type inference have to be performed.
        if (!read_line(file, line, newline_delimiter, column_delimiter,
                       columns)) {return;}

        // Categorical variable maps get stored in a map for later use.
        std::unordered_map<arma::uword, CatMap> cat_vars;
        if (!col_types.has_value()) {
            col_types = oop::stats::infer_types(line, cat_vars);
        }

        std::vector<oop::stats::sup_single_types> row = convert_strings(
                line, *col_types);
        matr.append_row(row);

        if (!full_header.empty()) {matr.set_column_labels(full_header);}

        // Append the rest of the CSV file, assuming constant types.
        while (read_line(file, line, newline_delimiter, column_delimiter,
                         columns)) {
            matr.append_row(convert_strings(line, *col_types));
        }

        // Add the categorical mappings if there are any.
        for (const auto &[key, value]:  cat_vars) {
            matr.set_map(key, value.get_swapped_map());
        }
    }
}

#endif //EXAMPLES_LOAD_HPP
