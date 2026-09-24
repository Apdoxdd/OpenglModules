cmake_minimum_required(VERSION 3.10)

project(smileWall C CXX)

add_subdirectory(../libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../libs/glad/include)

add_library(stb ../libs/stb/stb_image.cpp)
target_include_directories(stb PUBLIC ../libs/stb)

add_executable(smileWall main.cpp shader.cpp)
target_link_libraries(smileWall PRIVATE glfw glad stb)
