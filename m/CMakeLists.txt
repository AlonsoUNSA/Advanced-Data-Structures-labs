# Especifica la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Define el nombre del proyecto
project(BTreeProject)

# Especifica el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agrega los archivos fuente y de encabezado
set(SOURCES
    main.cpp
    # BTree.cpp
    Key.cpp
)

set(HEADERS
  # BTree.h
    Key.h
    BNode.h
)

# Crea el ejecutable a partir de los archivos fuente
add_executable(BTreeExecutable ${SOURCES} ${HEADERS})

