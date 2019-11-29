cmake_minimum_required(VERSION 3.14)
project(gravity)

add_subdirectory(glad)
find_package(glfw3)

add_executable(gravity main.c point.c shader.c window.c)
target_link_libraries(gravity glad glfw m)
