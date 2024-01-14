#ifndef ODE_TYPES_HPP
#define ODE_TYPES_HPP

#include <variant>
#include <tuple>
#include <functional>
#include "ode/ode_scal.hpp"
#include "ode/ode_vec.hpp"


namespace oop::ode::bindings {
    // (Function, y0, h, end)
    using sup_scal_init_types = std::variant<
//            std::tuple<std::function<int(int,int)>,int,int,int>,
//            std::tuple<std::function<long int(long int, long int)>, long int, long int, long int>,
//            std::tuple<std::function<long long int(long long int,long long int)>,long long int,long long int, long long int>,
//            std::tuple<std::function<float(float,float)>,float,float,float>,
            std::tuple<std::function<double(double,double)>,double,double,double>
//            std::tuple<std::function<unsigned int(unsigned int, unsigned int)>, unsigned int, unsigned int, unsigned int>,
//            std::tuple<std::function<unsigned long int(unsigned long int, unsigned long int)>, unsigned long int, unsigned long int, unsigned long int>,
//            std::tuple<std::function<unsigned long long int(unsigned long long int, unsigned long long int)>, unsigned long long int, unsigned long long int, unsigned long long int>
            >;

    using sup_vec_init_types = std::variant<
//            std::tuple<std::function<arma::Col<int>(int, arma::Col<int>)>, arma::Col<int>, int, int>,
//            std::tuple<std::function<arma::Col<long>(long, arma::Col<long>)>, arma::Col<long>, long, long>,
//            std::tuple<std::function<arma::Col<long long>(long long, arma::Col<long long>)>, arma::Col<long long>, long long, long long>,
//            std::tuple<std::function<arma::Col<float>(float, arma::Col<float>)>, arma::Col<float>, float, float>,
            std::tuple<std::function<arma::Col<double>(double, arma::Col<double>)>, arma::Col<double>, double, double>
//            std::tuple<std::function<arma::Col<unsigned>(unsigned, arma::Col<unsigned>)>, arma::Col<unsigned>, unsigned, unsigned>,
//            std::tuple<std::function<arma::Col<unsigned long >(unsigned long, arma::Col<unsigned long>)>, arma::Col<unsigned long>, unsigned long, unsigned long>,
//            std::tuple<std::function<arma::Col<unsigned long long >(unsigned long long, arma::Col<unsigned long long>)>, arma::Col<unsigned long long>, unsigned long long, unsigned long long>
            >;

    using sup_scal_euler = std::variant<
//            oop::ode_scal::Euler_Scal<int>,
//            oop::ode_scal::Euler_Scal<long int>,
//            oop::ode_scal::Euler_Scal<long long int>,
//            oop::ode_scal::Euler_Scal<float>,
            oop::ode_scal::Euler_Scal<double>
//            oop::ode_scal::Euler_Scal<unsigned int>,
//            oop::ode_scal::Euler_Scal<unsigned long int>,
//            oop::ode_scal::Euler_Scal<unsigned long long int>
            >;

    using sup_vec_euler = std::variant<
//            oop::ode_vec::Euler<int>,
//            oop::ode_vec::Euler<long int>,
//            oop::ode_vec::Euler<long long int>,
//            oop::ode_vec::Euler<float>,
            oop::ode_vec::Euler<double>
//            oop::ode_vec::Euler<unsigned int>,
//            oop::ode_vec::Euler<unsigned long int>,
//            oop::ode_vec::Euler<unsigned long long int>
            >;

    using sup_scal_midpoint = std::variant<
//            oop::ode_scal::Midpoint_Scal<int>,
//            oop::ode_scal::Midpoint_Scal<long int>,
//            oop::ode_scal::Midpoint_Scal<long long int>,
//            oop::ode_scal::Midpoint_Scal<float>,
            oop::ode_scal::Midpoint_Scal<double>
//            oop::ode_scal::Midpoint_Scal<unsigned int>,
//            oop::ode_scal::Midpoint_Scal<unsigned long int>,
//            oop::ode_scal::Midpoint_Scal<unsigned long long int>
            >;

    using sup_vec_midpoint = std::variant<
//            oop::ode_vec::Midpoint<int>,
//            oop::ode_vec::Midpoint<long int>,
//            oop::ode_vec::Midpoint<long long int>,
//            oop::ode_vec::Midpoint<float>,
            oop::ode_vec::Midpoint<double>
//            oop::ode_vec::Midpoint<unsigned int>,
//            oop::ode_vec::Midpoint<unsigned long int>,
//            oop::ode_vec::Midpoint<unsigned long long int>
            >;

    using sup_scal_rk4 = std::variant<
//            oop::ode_scal::RK4_Scal<int>,
//            oop::ode_scal::RK4_Scal<long int>,
//            oop::ode_scal::RK4_Scal<long long int>,
//            oop::ode_scal::RK4_Scal<float>,
            oop::ode_scal::RK4_Scal<double>
//            oop::ode_scal::RK4_Scal<unsigned int>,
//            oop::ode_scal::RK4_Scal<unsigned long int>,
//            oop::ode_scal::RK4_Scal<unsigned long long int>
            >;

    using sup_vec_rk4 = std::variant<
//            oop::ode_vec::RK4<int>,
//            oop::ode_vec::RK4<long int>,
//            oop::ode_vec::RK4<long long int>,
//            oop::ode_vec::RK4<float>,
            oop::ode_vec::RK4<double>
//            oop::ode_vec::RK4<unsigned int>,
//            oop::ode_vec::RK4<unsigned long int>,
//            oop::ode_vec::RK4<unsigned long long int>
            >;

    using sup_mat_types = std::variant<
//            arma::Mat<int>,
//            arma::Mat<long int>,
//            arma::Mat<long long int>,
//            arma::Mat<float>,
            arma::Mat<double>
//            arma::Mat<unsigned int>,
//            arma::Mat<unsigned long int>,
//            arma::Mat<unsigned long long int>
            >;

    using sup_col_types = std::variant<
//            arma::Col<int>,
//            arma::Col<long int>,
//            arma::Col<long long int>,
//            arma::Col<float>,
            arma::Col<double>
//            arma::Col<unsigned int>,
//            arma::Col<unsigned long int>,
//            arma::Col<unsigned long long int>
    >;

    typedef std::variant<
//            py::array_t<int>,
//            py::array_t<long int>,
//            py::array_t<long long int>,
//            py::array_t<float>,
            py::array_t<double>
//            py::array_t<unsigned int>,
//            py::array_t<unsigned long int>,
//            py::array_t<unsigned long long int>
            > sup_arr_types;
}
#endif //ODE_TYPES_HPP