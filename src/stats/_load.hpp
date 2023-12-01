//
// Created by uki on 11/30/23.
//

#ifndef EXAMPLES__LOAD_HPP
#define EXAMPLES__LOAD_HPP
#include <armadillo>
#include <string>
#include <fstream>
#include <ios>
#include "dataframe.hpp"

namespace oop::stats {
    // Infer the types of all elements in a vector of strings
    std::vector<std::string> infer_types(std::vector<std::string> row);

    // Split a string wherever some char is present
    std::vector<std::string> split_line(std::string line, char delimiter);

    union Columns {
        std::vector<std::string> vec_s;
        std::vector<int> vec_i;
        std::string s;
        int i;
    };

    oop::stats::DataFrame &load(std::string &filepath,
               oop::stats::Columns &columns,
               std::vector<std::string> col_types,
               bool header,
               char newline_delimiter,
               char column_delimiter) {
        std::fstream file(filepath, std::ios::in);
        if(!file.is_open()) {
            throw;
        }
        std::string line, word;
        if (header) {
            getline(file, line);
            std::string head{line};
        }
        getline(file, line);
        std::vector<std::string> split{split_line(line)};
        std::vector<std::string> types = oop::stats::infer_types(split);
        oop::stats::DataFrame matr;

        while(getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
}

#endif //EXAMPLES__LOAD_HPP
