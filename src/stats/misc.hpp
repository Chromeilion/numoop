//
// Created by chromeilion on 12/1/23.
//

#ifndef EXAMPLES_MISC_HPP
#define EXAMPLES_MISC_HPP

namespace oop::stats {
    // For overloading inside a std::visit call. Taken from the documentation:
    // https://en.cppreference.com/w/cpp/utility/variant/visit
    template<class... Ts>
    struct overloaded : Ts ... {
        using Ts::operator()...;
    };
    template<class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;
}

#endif //EXAMPLES_MISC_HPP
