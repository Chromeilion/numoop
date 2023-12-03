# Some Armadillo related code is taken from here:
# https://oceanai.mit.edu/svn/moos-ivp-pavlab-aro/src/lib_learning/CMakeLists.txt
# And some from here:
# https://github.com/mlpack/mlpack/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.22.1)
project(numoop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wpedantic -Werror")


find_package(Armadillo)
if (NOT ARMADILLO_FOUND)
    find_package(BLAS QUIET)
    find_package(LAPACK QUIET)
    if (NOT BLAS_FOUND AND NOT LAPACK_FOUND)
        message(FATAL_ERROR "Can not find BLAS or LAPACK!  These are required
        for Armadillo.  Please install one of them---or install
        Armadillo---before installing numoop.")
    endif()
    message("Using bundled Armadillo to compile")
    set(ARMADILLO_INCLUDE_DIR external/armadillo-code/include)
    find_package(Armadillo REQUIRED)
endif()

include_directories(${ARMADILLO_INCLUDE_DIRS})

# Include our header library
include_directories(src)

project(tests)
add_executable(tests tests/stats_test.cpp tests/ode_test.cpp)

# Link against BLAS and LAPACK for Armadillo
target_link_libraries(tests ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES}
        ${ARMADILLO_LIBRARIES})
