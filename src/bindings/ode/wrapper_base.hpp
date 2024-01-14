//
// Created by chromeilion on 1/14/24.
//

#ifndef NUMOOP_WRAPPER_BASE_HPP
#define NUMOOP_WRAPPER_BASE_HPP
#include "ode_types.hpp"
#include <pybind11/pybind11.h>
#include <variant>
#include <iostream/ Vector methods
        MakeBindings<sup_vec_euler, oop::ode_vec::Euler, VecWrap,
                sup_vec_init_types>(m, "Euler");
        MakeBindings<sup_vec_midpoint, oop::ode_vec::Midpoint, VecWrap,
                sup_vec_init_types>(m, "Midpoint");
        MakeBindings<sup_vec_rk4, oop::ode_vec::RK4, VecWrap,
                sup_vec_init_types>(m, "RK4");>

namespace py = pybind11;

namespace oop::ode::bindings {
    template<typename P, typename InitTypes>
    class BaseWrap {
    private:
        // Initialize internal_class with some init types
        virtual P apply_init(InitTypes&) = 0;
        virtual P&  get_ic() = 0;
    public:
        [[nodiscard]] sup_arr_types ode() {
            auto mat = std::visit(
                    [](auto& ic) {
                        auto res = ic.ode();
                        sup_arr_types np = {carma::to_numpy(res)};
                        return np;},
                    get_ic());
            return mat;
        }
        virtual ~BaseWrap() = default;
    };
}
#endif //NUMOOP_WRAPPER_BASE_HPP
