cmake_minimum_required(VERSION 3.22)

project(searchEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)


set(SOURCE_FILES src/main.cpp src/converter.h)








add_executable(searchEngine_run ${SOURCE_FILES} src/converter.h)



target_link_libraries(searchEngine_run)
target_link_libraries(searchEngine_run PRIVATE nlohmann_json::nlohmann_json)


add_subdirectory(unit_tests)











