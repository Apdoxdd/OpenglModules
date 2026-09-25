cmake_minimum_required(VERSION 3.10)

project(float C CXX)

add_subdirectory(../libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../libs/glad/include)

add_library(stb ../libs/stb/stb_image.cpp)
target_include_directories(stb PUBLIC ../libs/stb)

add_executable(float main.cpp shader.cpp)
target_link_libraries(float PRIVATE glfw glad stb)
