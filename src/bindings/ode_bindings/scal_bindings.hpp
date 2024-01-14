#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
#include <variant>
#include <functional>
#include <iostream>
#include <cstdlib>
#include <carma>
#include <tuple>

#include "ode/ode_scal.hpp"
#include "ode_types.hpp"
#include "stats/misc.hpp"

namespace py = pybind11;

namespace oop::ode::bindings {
    template <typename P>

    class ScalWrap {
    public:
        ScalWrap(sup_init_types& args){
                    std::visit(SetAll(), internal_class, args);
        }
        void set_func (const sup_scal_funcs& scal) {
            std::visit(oop::stats::overloaded{
                CallSetFunc(),
                [](auto &, auto &){throw py::type_error("Invalid type when setting function!");}
            }, internal_class, scal);
        }
        void set_y0 (const sup_scal_types& scal) {
            std::visit(oop::stats::overloaded{
                [](auto &ic, auto &sc){ic.set_y0(sc);},
            }, internal_class, scal);
        }
        void set_h (const sup_scal_types& scal) {
            std::visit(oop::stats::overloaded{
                CallSetH(),
                [](auto &, auto &){throw py::type_error("Invalid type when setting step!");}
            }, internal_class, scal);
        }
        void set_end (const sup_scal_types& scal) {
            std::visit(oop::stats::overloaded{
                CallSetEnd(),
                [](auto &, auto &){throw py::type_error("Invalid type when setting final time!");}
            }, internal_class, scal);
        }
        sup_mat_types ode () {
            return std::visit([](auto &ic){return sup_mat_types{ic.ode()};}, internal_class);
        }

    private:
        P internal_class;

        class CallSetFunc {
            public:
            template <template <typename W> typename Y, typename W>
            void operator()(Y<W> &meth, const std::function<W(W,W)> &w){
                return meth.set_func(w);
            }
        };
        class CallSetY0 {
            public:
            template <template <typename W> typename Y, typename W>
            void operator()(Y<W> &meth, W &w){
                return meth.set_y0(w);
            }
        };
        class CallSetH {
            public:
            template <template <typename W> typename Y, typename W>
            void operator()(Y<W> &meth, W &w){
                return meth.set_h(w);
            }
        };
        class CallSetEnd {
            public:
            template <template <typename W> typename Y, typename W>
            void operator()(Y<W> &meth, W &w){
                return meth.set_end(w);
            }
        };
        class SetAll {
            public:
            template <template <typename W> typename Y, typename W>
            void operator()(Y<W> &meth, std::tuple<std::function<W(W,W)>, W, W, W> tuple){
                
                meth.set_func(std::get<0>(tuple));
                meth.set_y0(std::get<1>(tuple));
                meth.set_h(std::get<2>(tuple));
                meth.set_end(std::get<3>(tuple));
            }
        };        
    };
    
    template <typename C>
    void MakeBindings(py::module& m, const char* module_name) {
    py::class_<ScalWrap<C>>(m, module_name)
        .def(py::init<sup_init_types>())
        .def("ode", &ScalWrap<C>::ode);
    }

 }// namespace oop::ode::bindings