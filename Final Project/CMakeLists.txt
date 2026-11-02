cmake_minimum_required(VERSION 3.16)
project(lasso_regression VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

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
    src/member10_cross_validation.cpp
)
add_library(group14::lasso_regression ALIAS lasso_regression)

add_library(linear_regression src/linear_regression.cpp)
add_library(group14::linear_regression ALIAS linear_regression)

add_executable(lasso_week2_demo examples/week2_demo.cpp)
target_link_libraries(lasso_week2_demo PRIVATE lasso_regression)

add_executable(lasso_week3_demo examples/week3_demo.cpp)
target_link_libraries(lasso_week3_demo PRIVATE lasso_regression)

add_executable(lasso_week4_demo examples/week4_demo.cpp)
target_link_libraries(lasso_week4_demo PRIVATE lasso_regression)

add_executable(lasso_csv_demo examples/load_csv_demo.cpp)
target_link_libraries(lasso_csv_demo PRIVATE lasso_regression)

add_executable(lasso_baseline_demo examples/member05_baseline.cpp)
target_link_libraries(lasso_baseline_demo PRIVATE linear_regression)

add_executable(lasso_cost_demo examples/member06_cost.cpp)
target_link_libraries(lasso_cost_demo PRIVATE lasso_regression)

add_executable(lasso_soft_threshold_demo examples/member07_soft_threshold.cpp)
target_link_libraries(lasso_soft_threshold_demo PRIVATE lasso_regression)

add_executable(lasso_lambda_demo examples/member08_tuning.cpp)
target_link_libraries(lasso_lambda_demo PRIVATE lasso_regression)

add_executable(linear_regression_demo examples/linear_regression_demo.cpp)
target_link_libraries(linear_regression_demo PRIVATE linear_regression)

enable_testing()

add_executable(lasso_week2_tests tests/test_week2.cpp)
target_link_libraries(lasso_week2_tests PRIVATE lasso_regression)
add_test(NAME lasso_week2_tests COMMAND lasso_week2_tests)

add_executable(lasso_week3_tests tests/test_week3.cpp)
target_link_libraries(lasso_week3_tests PRIVATE lasso_regression)
add_test(NAME lasso_week3_tests COMMAND lasso_week3_tests)

add_executable(lasso_week4_tests tests/test_week4.cpp)
target_link_libraries(lasso_week4_tests PRIVATE lasso_regression)
add_test(NAME lasso_week4_tests COMMAND lasso_week4_tests)

add_executable(linear_regression_tests tests/test_linear_regression.cpp)
target_link_libraries(linear_regression_tests PRIVATE linear_regression)
add_test(NAME linear_regression_tests COMMAND linear_regression_tests)

set_tests_properties(
    lasso_week2_tests
    lasso_week3_tests
    lasso_week4_tests
    linear_regression_tests
    PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

foreach(library_target IN ITEMS lasso_regression linear_regression)
    target_include_directories(${library_target} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
endforeach()

install(TARGETS lasso_regression linear_regression
    EXPORT Group14RegressionTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT Group14RegressionTargets
    FILE Group14RegressionTargets.cmake
    NAMESPACE group14::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Group14Regression
)

configure_package_config_file(
    cmake/Group14RegressionConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/Group14RegressionConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Group14Regression
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/Group14RegressionConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/Group14RegressionConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/Group14RegressionConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Group14Regression
)
