# Some Armadillo related code is taken from here:
# https://oceanai.mit.edu/svn/moos-ivp-pavlab-aro/src/lib_learning/CMakeLists.txt
# And some from here:
# https://github.com/mlpack/mlpack/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.22.1)
project(numoop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Dependencies
add_subdirectory(external/armadillo-code REQUIRED)
# Python bindings
find_package(Python COMPONENTS Interpreter Development)
add_subdirectory(external/pybind11)
add_subdirectory(external/carma)

# Include dirs
include_directories(src)

add_executable(test_ode tests/ode_test.cpp)
add_executable(tests tests/stats_test.cpp)
pybind11_add_module(python_bindings bindings/dataframe.cpp)

target_link_libraries(python_bindings PRIVATE carma::carma)
target_link_libraries(tests armadillo GTest::gtest_main)
target_link_libraries(test_ode armadillo GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
