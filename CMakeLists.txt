cmake_minimum_required(VERSION 3.22)

project(SearchEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

set(SOURCE_FILES src/main.cpp include/converter.h include/invertedIndex.h src/invertedIndex.cpp include/update.h include/searchServer.h)

add_executable(SearchEngineRun ${SOURCE_FILES} include/converter.h)

target_link_libraries(SearchEngineRun)

target_link_libraries(SearchEngineRun PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(UnitTests)











