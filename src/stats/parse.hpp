//
// Created by chromeilion on 12/2/23.
//

#ifndef EXAMPLES_PARSE_HPP
#define EXAMPLES_PARSE_HPP
#include <regex>

namespace oop::stats {
    // A vector of functions that convert a string to some supported type.
    typedef std::function<sup_single_types(const std::string&)> convert_func;

    // Regex to check if a string is a number.
    static const std::regex is_number{
            R"([+-]?(\d+([.]\d*)?(e[+-]?\d+)?|[.]\d+(e[+-]?\d+)?))"};

    // Check if there is a dot in a string.
    static const std::regex find_dot{R"([.])"};

    // Convert a vector of strings to types supported by the DataFrame
    std::vector<oop::stats::sup_single_types> convert_strings(
            std::vector<std::string> strings,
            std::vector<convert_func> types);

    // A functor that takes a string and maps it to a number. It keeps track of
    // what string is mapped to what number. Useful when converting a
    // categorical variable into ints.
    class CatMap {
        arma::uword no_cats = 0;
    public:
        std::unordered_map<std::string, arma::uword> cat_map;
        std::unordered_map<arma::uword, std::string> get_swapped_map() const;

        // Take string and return a number unique to that string.
        arma::uword &operator()(const std::string& str);
    };

    // Infer the types of all elements in a vector of strings.
    std::vector<convert_func> infer_types(
            const std::vector<std::string> &row,
            std::optional<std::unordered_map<arma::uword, CatMap>> cat_vars = std::nullopt);

    // Implementation

    static const auto str_float = [](const std::string& x){return std::stof(x);};
    static const auto str_intll = [](const std::string& x){return std::stoll(x);};

    arma::uword &CatMap::operator()(const std::string& str) {
        if (this->cat_map.find(str) == this->cat_map.end()) {
            this->cat_map[str] = this->no_cats++;
        }
        return this->cat_map[str];
    }

    std::unordered_map<arma::uword, std::string>
    CatMap::get_swapped_map() const {
        std::unordered_map<arma::uword, std::string> new_map;
        for (auto& [key, value]: cat_map) {
            new_map[value] = key;}
        return new_map;
    }

    std::vector<convert_func> infer_types(
            const std::vector<std::string> &row,
            std::optional<std::unordered_map<arma::uword, CatMap>> cat_vars) {
        std::vector<convert_func> types_vec;
        for (auto& str : row) {
            if (std::regex_match(str, is_number)) {
                if (str.find(".") != std::string::npos) {
                    types_vec.emplace_back(str_float);
                }
                else {types_vec.emplace_back(str_intll);}
            }
            else {
                CatMap cm;
                if (cat_vars.has_value()) {(*cat_vars)[types_vec.size()-1] = (cm);}
                types_vec.emplace_back(cm);
            }
        }
        return types_vec;
    }

    // Convert a vector of strings to types supported by the DataFrame
    std::vector<oop::stats::sup_single_types> convert_strings(
            std::vector<std::string> strings,
            std::vector<convert_func> types) {
        std::vector<oop::stats::sup_single_types> new_col;
        for (std::size_t i = 0; i < strings.size(); ++i) {
            new_col.push_back(types[i](strings[i]));
        }
        return new_col;
    }
}

#endif //EXAMPLES_PARSE_HPP