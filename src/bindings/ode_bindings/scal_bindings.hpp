#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>
#include <variant>
#include <functional>

#include "ode/ode_scal.hpp"
#include "ode_types.hpp"
#include "stats/misc.hpp"

namespace py = pybind11;

namespace oop::ode::bindings {
    template <typename P>

    class ScalWrap {
    public:
        ScalWrap(sup_scal_types scal){
            std::visit([](auto & ic, auto & st){
                ic.set_y0(st);
            }, internal_class, scal);
        }
        void set_func (const sup_scal_funcs& scal) {
            std::visit(oop::stats::overloaded{
                CallMeth(),
                [](auto &, auto &){throw py::type_error("Invalid type when setting function!");}
            }, internal_class, scal);
        }
        //void set_y0 (const sup_scal_types& scal) {
        //    std::visit(oop::stats::overloaded{
        //        CallMeth(),
        //        [](auto &, auto &){throw py::type_error("Invalid type when setting initial conditions!");}
        //    }, internal_class, scal);
        //}

    private:
        P internal_class;
        void set_interal_class(P internal_class_) {
            this->internal_class = internal_class_;
        }

        class CallMeth {
            public:
            template <template <typename W> typename Y, typename W>
            void operator()(Y<W> meth, const std::function<W(W,W)> w){
                return meth.set_func(w);
            }
            //template<template <typename W> typename Y, typename W>
            //std::invoke_result_t<Y> operator()(Y<W> meth, W w){
            //    return meth(w);
            //}
        };
    };
    
    template <typename C>
    void MakeBindings(py::module& m, const std::string module_name) {
    py::class_<ScalWrap<C>>(m, module_name)
        .def(py::init<sup_scal_types>())
        .def("set_func", &ScalWrap<C>::set_func);
        //.def("set_y0", &ScalWrap<C>::set_y0);
    }   
        //        .def("set_h", &ODE_Scal<T>::set_h)
        //        .def("set_end", &ODE_Scal<T>::set_end)
        //        .def("ode", &ODE_Scal<T>::ode);
    
    
 }// namespace oop::ode::bindings