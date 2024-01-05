enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest extern/googletest)
include(GoogleTest)

add_executable(
        tests
        stats_test.cpp
        ode_test.cpp
)
target_link_libraries(
        tests
        armadillo
        GTest::gtest_main
)
gtest_discover_tests(tests)
