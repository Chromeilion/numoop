cmake_minimum_required(VERSION 3.22.1)
project(numoop)

set(CMAKE_CXX_STANDARD 17)

find_package(BLAS REQUIRED)

include_directories(./external/armadillo-code/include -DARMA_DONT_USE_WRAPPER
        ./external/armadillo-code/include/armadillo_bits)
include_directories(${BLAS_INCLUDE_DIR})

add_library(numoop src/library.cpp)

project(examples)
add_executable(examples examples/example_program.cpp)
target_link_libraries(examples ${BLAS_LIBRARIES})
target_link_libraries(src/include)
target_compile_options(examples PRIVATE ${BLAS_LINKER_FLAGS})
