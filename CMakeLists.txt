cmake_minimum_required(VERSION 3.26)
project(numoop)

set(CMAKE_CXX_STANDARD 17)

find_package(BLAS REQUIRED)

include_directories(./external/armadillo-code/include -DARMA_DONT_USE_WRAPPER
        ./external/armadillo-code/include/armadillo_bits)
include_directories(${BLAS_INCLUDE_DIR})

add_library(numoop src/library.cpp
        examples/example_program.cpp)
target_compile_options(numoop PRIVATE ${BLAS_LINKER_FLAGS})

target_link_libraries(numoop ${BLAS_LIBRARIES})
