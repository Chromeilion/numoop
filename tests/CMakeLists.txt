enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest extern/googletest)
include(GoogleTest)

add_executable(
        tests
        test_stats.cpp
        test_ode.cpp
)
target_link_libraries(
        tests
        armadillo
        GTest::gtest_main
)
gtest_discover_tests(tests)
