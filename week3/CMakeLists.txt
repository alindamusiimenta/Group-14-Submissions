cmake_minimum_required(VERSION 3.16)
project(lasso_regression_week3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lasso_regression
    src/lasso_regression.cpp
    src/member01_data.cpp
    src/member02_preprocessing.cpp
    src/member03_scaling.cpp
    src/member04_matrix.cpp
    src/member06_cost.cpp
    src/member07_soft_threshold.cpp
    src/member08_coordinate.cpp
    src/member09_evaluation.cpp
)
target_include_directories(lasso_regression PUBLIC include)
target_compile_options(lasso_regression PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lasso_week3_demo examples/week3_demo.cpp)
target_link_libraries(lasso_week3_demo PRIVATE lasso_regression)

add_executable(lasso_week2_tests tests/test_week2.cpp)
target_link_libraries(lasso_week2_tests PRIVATE lasso_regression)

add_executable(lasso_week3_tests tests/test_week3.cpp)
target_link_libraries(lasso_week3_tests PRIVATE lasso_regression)

enable_testing()
add_test(NAME lasso_week2_tests COMMAND lasso_week2_tests)
add_test(NAME lasso_week3_tests COMMAND lasso_week3_tests)