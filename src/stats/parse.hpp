//
// Created by chromeilion on 12/2/23.
//

#ifndef EXAMPLES_PARSE_HPP
#define EXAMPLES_PARSE_HPP
#include <regex>
#include <limits>

namespace oop::stats {
    // A vector of functions that convert a string to some supported type.
    typedef std::function<sup_single_types(const std::string&)> convert_func;

    // Regex to check if a string is a number.
    static const std::regex is_number{
            R"([+-]?(\d+([.]\d*)?(e[+-]?\d+)?|[.]\d+(e[+-]?\d+)?))"};

    // Convert a vector of strings to types supported by the DataFrame
    inline std::vector<oop::stats::sup_single_types> convert_strings(
            std::vector<std::string> &strings,
            std::vector<convert_func> &types,
            const std::optional<std::vector<int>> &columns);

    // A functor that takes a string and maps it to a number. It keeps track of
    // what string is mapped to what number. Useful when converting a
    // categorical variable into ints.
    class CatMap {
        arma::uword no_cats = 0;
    public:
        std::unordered_map<std::string, arma::uword> cat_map;
        inline std::unordered_map<arma::uword, std::string> get_swapped_map() const;

        // Take string and return a number unique to that string.
        inline arma::uword &operator()(const std::string& str);
    };

    // Infer the types of all elements in a vector of strings.
    inline std::vector<convert_func> infer_types(
            const std::vector<std::string> &row,
            std::vector<std::string> &col_types,
            std::vector<arma::uword> &cat_vars);

    // Implementation

    static const auto str_float = [](const std::string& x){
        try {return std::stof(x);} catch (std::invalid_argument&)
        { return std::numeric_limits<float>::quiet_NaN(); }};
    static const auto str_intll = [](const std::string& x){
        try {return std::stoll(x);} catch (std::invalid_argument&)
        { return std::numeric_limits<long long>::quiet_NaN(); }};

    inline arma::uword &CatMap::operator()(const std::string& str) {
        if (this->cat_map.count(str) == 0) {
            this->cat_map.insert({str, this->no_cats++});
        }
        return this->cat_map[str];
    }

    std::unordered_map<arma::uword, std::string>
    inline CatMap::get_swapped_map() const {
        std::unordered_map<arma::uword, std::string> new_map;
        for (auto& [key, value]: cat_map) {
            new_map[value] = key;}
        return new_map;
    }

    inline std::vector<convert_func> infer_types(
            const std::vector<std::string> &row,
            std::vector<std::string> &col_types,
            std::vector<arma::uword> &cat_vars) {
        std::vector<convert_func> types_vec;
        for (auto& str : row) {
            if (std::regex_match(str, is_number)) {
                if (str.find(".") != std::string::npos) {
                    types_vec.emplace_back(str_float);
                    col_types.emplace_back("float");
                }
                else {
                    types_vec.emplace_back(str_intll);
                    col_types.emplace_back("long long");
                }
            }
            else {
                CatMap cm;
                types_vec.emplace_back(cm);
                cat_vars.push_back(types_vec.size()-1);
                col_types.emplace_back("Catagorical (arma::uword)");
            }
        }
        return types_vec;
    }

    // Convert a vector of strings to types supported by the DataFrame
    inline std::vector<oop::stats::sup_single_types> convert_strings(
            std::vector<std::string> &strings,
            std::vector<convert_func> &types,
            const std::optional<std::vector<int>> &columns) {
        std::vector<oop::stats::sup_single_types> new_col;
        if (columns.has_value()) {
            for (arma::uword i=0;i<(*columns).size();++i) {
                new_col.push_back(types[i](strings[i]));
            }
        } else {
            for (std::size_t i = 0; i < strings.size(); ++i) {
                new_col.push_back(types[i](strings[i]));
            }
        }
        return new_col;
    }
}

#endif //EXAMPLES_PARSE_HPP