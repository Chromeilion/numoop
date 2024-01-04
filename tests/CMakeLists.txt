macro(add_new_test NAME)
    add_executable(
        ${NAME}
        ${NAME}.cpp
    )
    target_link_libraries(
        ${NAME}
        armadillo
        GTest::gtest_main
    )
    gtest_discover_tests(${NAME})
endmacro()

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest extern/googletest)
include(GoogleTest)

add_new_test(stats_test)
add_new_test(ode_test)
