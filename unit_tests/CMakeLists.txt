project(unit_tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

add_executable(unit_tests_run main_test.cpp)

target_link_libraries(unit_tests_run)

target_link_libraries(unit_tests_run gtest gtest_main)