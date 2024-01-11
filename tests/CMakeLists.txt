enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest extern/googletest)
include(GoogleTest)

add_executable(
        test_stats
        test_stats.cpp
)
add_executable(
        test_ode
        test_ode.cpp
)
target_link_libraries(
        test_stats
        armadillo
        GTest::gtest_main
)
target_link_libraries(
        test_ode
        armadillo
        GTest::gtest_main
)
gtest_discover_tests(test_stats test_ode)
