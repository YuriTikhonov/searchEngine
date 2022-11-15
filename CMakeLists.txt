cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME searchEngine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)


set(JSON_BuildTests OFF CACHE INTERNAL "")




add_subdirectory(nlohmann_json)

add_executable(${PROJECT_NAME} src/main.cpp include/converter.h unit_tests/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json gtest_main)

add_subdirectory(unit_tests)