cmake_minimum_required(VERSION 3.10)
project(paint)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Paint main.cpp)

if (WIN32)
    message(STATUS "Configurando dependências para Windows (MinGW)...")
    target_link_libraries(Paint opengl32 glu32 freeglut)

elseif (UNIX AND NOT APPLE)
    message(STATUS "Configurando dependências para Linux...")
    target_link_libraries(Paint GL glut GLU)
endif()