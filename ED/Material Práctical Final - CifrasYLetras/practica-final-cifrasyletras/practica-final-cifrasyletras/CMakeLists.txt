cmake_minimum_required(VERSION 3.13)
project(Practica_final_Juego_letras)

set(CMAKE_CXX_STANDARD 14)

set(BASE_FOLDER .)

# ========================================
# Incluir cabeceras
# ========================================
include_directories(${BASE_FOLDER}/include)

# ========================================
# Crear carpeta bin para los ejecutables
# ========================================
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ========================================
# Lista de módulos comunes
# ========================================
set(SOURCES_COMMON
    ${BASE_FOLDER}/src/bolsa_letras.cpp
    ${BASE_FOLDER}/src/diccionario.cpp
    ${BASE_FOLDER}/src/letras.cpp
)

# ========================================
# Ejecutable: letras_set (main)
# ========================================
add_executable(letras_set
    ${BASE_FOLDER}/src/letras_set.cpp    # main
    ${SOURCES_COMMON}
)

# ========================================
# Doxygen (documentación)
# ========================================
find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen build started")

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else()
    message("Doxygen needs to be installed to generate documentation")
endif()
