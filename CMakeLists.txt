cmake_minimum_required(VERSION 3.18.2)

if(SKBUILD)
    project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION} LANGUAGES CXX)
else()
    project(numoop)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Python bindings
find_package(Python COMPONENTS Interpreter Development.Module NumPy REQUIRED)
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})

if(${CMAKE_BUILD_TYPE} EQUAL "DEBUG")
    OPTION(ENABLE_CARMA_EXTRA_DEBUG "Enable CARMA_EXTRA_DEBUG" ON)
    OPTION(ENABLE_ARMA_EXTRA_DEBUG "Enable ARMA_EXTRA_DEBUG" ON)
else()
    OPTION(ENABLE_ARMA_NO_DEBUG "Enable ENABLE_ARMA_NO_DEBUG" OFF)
endif()

# Dependencies
add_subdirectory(extern/pybind11)
add_subdirectory(extern/carma)

# Include our header library
include_directories(src)

# Tests
add_subdirectory(tests)

# Add Python Bindings
pybind11_add_module(_numoop MODULE src/bindings/dataframe.cpp)
target_link_libraries(_numoop PRIVATE carma::carma)

if(SKBUILD)
    install(TARGETS _numoop LIBRARY DESTINATION numoop)
endif()
