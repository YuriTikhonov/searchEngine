cmake_minimum_required(VERSION 3.22)
project(searchEngine)

set(CMAKE_CXX_STANDARD 17)
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

FetchContent_MakeAvailable(googletest)
enable_testing()


add_subdirectory(nlohmann_json)

add_executable(searchEngine main.cpp converter.h)

target_link_libraries(searchEngine PRIVATE nlohmann_json::nlohmann_json gtest_main)

include(GoogleTest)
gtest_discover_tests(searchEngine)