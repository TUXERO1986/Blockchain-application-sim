cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(Blockchain_Sim CXX)

# Usar el estándar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Buscar la librería OpenSSL instalada en el sistema (Necesaria para SHA-256)
find_package(OpenSSL REQUIRED)

# Indicar a CMake dónde buscar los archivos de cabecera (.h)
include_directories(include)

# Definir los archivos fuente (.cpp) con los nombres corregidos
set(SOURCES
    src/main.cpp
    src/Block.cpp
    src/Blockchain.cpp
    src/TracerValidator.cpp
)

# Crear el ejecutable combinando los archivos fuente
add_executable(Blockchain_Sim ${SOURCES})

# Enlazar las librerías criptográficas de OpenSSL al ejecutable
target_link_libraries(Blockchain_Sim OpenSSL::SSL OpenSSL::Crypto)