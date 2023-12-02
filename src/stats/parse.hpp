//
// Created by chromeilion on 12/2/23.
//

#ifndef EXAMPLES_PARSE_HPP
#define EXAMPLES_PARSE_HPP

namespace oop::stats {
    // A vector of functions that convert a string to some supported type.
    typedef std::function<sup_single_types(std::string)> convert_func;

    // Convert a vector of strings to types supported by the DataFrame
    std::vector<oop::stats::sup_single_types> convert_strings(
            std::vector<std::string> strings,
            std::vector<convert_func> types);

    // Infer the types of all elements in a vector of strings.
    const std::vector<convert_func> infer_types(
            const std::vector<std::string> &row);

    // Implementation

    

}

#endif //EXAMPLES_PARSE_HPP