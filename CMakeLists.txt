cmake_minimum_required(VERSION 3.22)
project(image_processor)

set(CMAKE_CXX_STANDARD 14)

# Must set the path to the main.cpp, for example: src/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} src/main.cpp
        src/utils/image_conversions.h
        src/utils/image_conversions.cpp
        src/utils/util.h
        src/utils/util.cpp
        src/utils/starting_matrices.h)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})