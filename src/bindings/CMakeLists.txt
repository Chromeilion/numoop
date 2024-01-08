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
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/pybind11 extern/pybind11)
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/carma extern/carma)

# Add Python Bindings
pybind11_add_module(_numoop MODULE
        _numoop.cpp
        load_bindings.cpp
        load_bindings.hpp
)
target_link_libraries(_numoop PRIVATE carma::carma)

add_subdirectory(dataframe_bindings)
add_subdirectory(ode_bindings)
