#ifndef ODE_TYPES_HPP
#define ODE_TYPES_HPP

#include <variant>
#include <tuple>
#include <functional>
#include "ode/ode_scal.hpp"

namespace oop::ode::bindings {
using sup_init_types = std::variant <std::tuple<std::function<int(int,int)>,int,int,int>,
                                    std::tuple<std::function<long int(long int, long int)>, long int, long int, long int>,
                                    std::tuple<std::function<long long int(long long int,long long int)>,long long int,long long int, long long int>,
                                    std::tuple<std::function<float(float,float)>,float,float,float>,
                                    std::tuple<std::function<double(double,double)>,double,double,double>,
                                    std::tuple<std::function<unsigned int(unsigned int, unsigned int)>, unsigned int, unsigned int, unsigned int>,
                                    std::tuple<std::function<unsigned long int(unsigned long int, unsigned long int)>, unsigned long int, unsigned long int, unsigned long int>,
                                    std::tuple<std::function<unsigned long long int(unsigned long long int, unsigned long long int)>, unsigned long long int, unsigned long long int, unsigned long long int>>;

using sup_scal_types = std::variant <int, 
                                    long int,   
                                    long long int, 
                                    float, 
                                    double, 
                                    unsigned int, 
                                    unsigned long int,
                                    unsigned long long int>;

using sup_vec_types = std::variant <
                      arma::Col<int>,
                      arma::Col<long int>,
                      arma::Col<long long int>,
                      arma::Col<float>,
                      arma::Col<double>,
                      arma::Col<unsigned int>,
                      arma::Col<unsigned long int>,
                      arma::Col<unsigned long long int>>;

using sup_scal_euler = std::variant <
                        oop::ode_scal::Euler_Scal<int>,
                        oop::ode_scal::Euler_Scal<long int>,
                        oop::ode_scal::Euler_Scal<long long int>,
                        oop::ode_scal::Euler_Scal<float>,
                        oop::ode_scal::Euler_Scal<double>,
                        oop::ode_scal::Euler_Scal<unsigned int>,
                        oop::ode_scal::Euler_Scal<unsigned long int>,
                        oop::ode_scal::Euler_Scal<unsigned long long int>>;

using sup_scal_midpoint = std::variant <
                        oop::ode_scal::Midpoint_Scal<int>,
                        oop::ode_scal::Midpoint_Scal<long int>,
                        oop::ode_scal::Midpoint_Scal<long long int>,
                        oop::ode_scal::Midpoint_Scal<float>,
                        oop::ode_scal::Midpoint_Scal<double>,
                        oop::ode_scal::Midpoint_Scal<unsigned int>,
                        oop::ode_scal::Midpoint_Scal<unsigned long int>,
                        oop::ode_scal::Midpoint_Scal<unsigned long long int>>;

using sup_scal_rk4 = std::variant <
                        oop::ode_scal::RK4_Scal<int>,
                        oop::ode_scal::RK4_Scal<long int>,
                        oop::ode_scal::RK4_Scal<long long int>,
                        oop::ode_scal::RK4_Scal<float>,
                        oop::ode_scal::RK4_Scal<double>,
                        oop::ode_scal::RK4_Scal<unsigned int>,
                        oop::ode_scal::RK4_Scal<unsigned long int>,
                        oop::ode_scal::RK4_Scal<unsigned long long int>>;

using sup_scal_funcs = std::variant <
                        std::function<int(int,int)>,
                        std::function<long int(long int,long int)>,
                        std::function<long long int(long long int,long long int)>,
                        std::function<float(float,float)>,
                        std::function<double(double,double)>,
                        std::function<unsigned int(unsigned int,unsigned int)>,
                        std::function<unsigned long int(unsigned long int,unsigned long int)>,
                        std::function<unsigned long long int(unsigned long long int,unsigned long long int)>>;

using sup_mat_types = std::variant <
                        arma::Mat<int>,
                        arma::Mat<long int>,
                        arma::Mat<long long int>, 
                        arma::Mat<float>, 
                        arma::Mat<double>, 
                        arma::Mat<unsigned int>,                    
                        arma::Mat<unsigned long int>, 
                        arma::Mat<unsigned long long int>>;
}
#endif //ODE_TYPES_HPP