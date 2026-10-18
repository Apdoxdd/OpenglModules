cmake_minimum_required(VERSION 3.10)

project(revise C CXX)

add_subdirectory(../libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../libs/glad/include)

add_library(stb ../libs/stb/stb_image.cpp)
target_include_directories(stb PUBLIC ../libs/stb)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(revise main.cpp shader.cpp)
target_link_libraries(revise PRIVATE glfw glad stb)
