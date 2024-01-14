//
// Created by chromeilion on 1/14/24.
//

#ifndef NUMOOP_WRAPPER_VEC_HPP
#define NUMOOP_WRAPPER_VEC_HPP
#include "ode_types.hpp"
#include "wrapper_base.hpp"
#include <pybind11/pybind11.h>
#include <variant>

namespace py = pybind11;

namespace oop::ode::bindings {
    template<typename P, template<typename> typename CN>
    class VecWrap : public BaseWrap<P, sup_vec_init_types> {
    private:
        P internal_class;
        class InitIC {
        public:
            template<typename W>
            P operator()(std::tuple<
                std::function<arma::Col<W>(W, arma::Col<W>)>,
                        arma::Col<W>, W, W> &args) {
                return P{CN<W>{
                        std::get<0>(args),
                        std::get<1>(args),
                        std::get<2>(args),
                        std::get<3>(args)
                }};
            }
        };
        P apply_init(sup_vec_init_types& args) override {
            return std::visit(InitIC(), args);
        };
        P& get_ic() override {return internal_class;}
    public:
        explicit VecWrap(sup_vec_init_types& args_) :
        internal_class{apply_init(args_)} {}
    };
}
#endif //NUMOOP_WRAPPER_VEC_HPP

