//
// Created by chromeilion on 1/14/24.
//

#ifndef NUMOOP_WRAPPER_SCAL_HPP
#define NUMOOP_WRAPPER_SCAL_HPP
#include "wrapper_base.hpp"


namespace oop::ode::bindings {
    template <typename P, template<typename>typename CN>
    class ScalWrap : public BaseWrap<P, sup_scal_init_types> {
    private:
        P internal_class;

        class InitIC {
        public:
            template<typename W>
            P operator()(const std::tuple<
                    std::function<W(W, W)>, W, W, W> &args) {
                return P{CN<W>{
                        std::get<0>(args),
                        std::get<1>(args),
                        std::get<2>(args),
                        std::get<3>(args)
                }};
            }
        };
        P apply_init(sup_scal_init_types& args) override {
            return std::visit(InitIC(), args);
        };
        P& get_ic() override {return internal_class;}
    public:
        explicit ScalWrap(sup_scal_init_types& args_) :
        internal_class{apply_init(args_)} {}
    };
}

#endif //NUMOOP_WRAPPER_SCAL_HPP
