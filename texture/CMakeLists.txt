cmake_minimum_required(VERSION 3.10)

project(texture C CXX)

add_subdirectory(../libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../libs/glad/include)

add_executable(texture main.cpp shader.cpp)
target_link_libraries(texture PRIVATE glfw glad)
