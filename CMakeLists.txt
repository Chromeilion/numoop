cmake_minimum_required(VERSION 3.18.2)

if(SKBUILD)
    project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION} LANGUAGES CXX)
else()
    project(numoop)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Our library
include_directories(include)
add_subdirectory(src)

# Tests
add_subdirectory(tests)

if(SKBUILD)
    install(TARGETS _numoop LIBRARY DESTINATION ${SKBUILD_PROJECT_NAME})
endif()
