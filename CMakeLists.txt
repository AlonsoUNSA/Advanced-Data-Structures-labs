cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(AVLmixedTree)

# Especifica el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agrega los archivos fuente
add_executable(AVLexec main.cpp Tree.cpp)

