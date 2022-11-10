cmake_minimum_required(VERSION 3.22)
project(searchEngine)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(searchEngine main.cpp)

target_link_libraries(searchEngine PRIVATE nlohmann_json::nlohmann_json)