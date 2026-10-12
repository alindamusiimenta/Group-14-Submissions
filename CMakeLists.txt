cmake_minimum_required(VERSION 3.16)
project(lasso_regression_week2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lasso_regression
    src/lasso_regression.cpp
    member02_preprocessing.cpp
    src/member03_scaling.cpp
    member04_matrix.cpp
    src/member08_coordinate_descent.cpp
    member09_evaluation.cpp
)
target_include_directories(lasso_regression PUBLIC include)
target_compile_options(lasso_regression PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lasso_week2_demo examples/week2_demo.cpp)
target_link_libraries(lasso_week2_demo PRIVATE lasso_regression)

add_executable(lasso_week2_tests tests/test_week2.cpp)
target_link_libraries(lasso_week2_tests PRIVATE lasso_regression)
enable_testing()
add_test(NAME lasso_week2_tests COMMAND lasso_week2_tests)
