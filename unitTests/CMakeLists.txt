project(UnitTests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

add_executable(UnitTestsRun mainTest.cpp)

target_link_libraries(UnitTestsRun)

target_link_libraries(UnitTestsRun gtest gtest_main)