cmake_minimum_required(VERSION 3.28)
project(Mini_Ray_Marching C)

set(CMAKE_C_STANDARD 23)

add_executable(Mini_Ray_Marching main.c)
find_package(FreeGLUT CONFIG REQUIRED)
target_link_libraries(Mini_Ray_Marching PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)