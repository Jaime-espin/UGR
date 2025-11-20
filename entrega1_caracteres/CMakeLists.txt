cmake_minimum_required(VERSION 3.29)
project(entrega1_caracteres)

set(CMAKE_CXX_STANDARD 14)

# Create separate executables for each file with main
add_executable(aspect_ratio_exe aspect_ratio/aspect_ratio.cpp)
add_executable(valor_ascii_exe valor_ascii/valor_ascii.cpp)
add_executable(consumo_dia_exe consumo_dia/consumo_dia.cpp)
add_executable(letra_alfabeto_exe letra_alfabeto/letra_alfabeto.cpp)