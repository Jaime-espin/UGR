cmake_minimum_required(VERSION 3.13)
project(TDA_pilas_colas)

set(CMAKE_CXX_STANDARD 14)

set(BASE_FOLDER ./)

# Carpeta donde se guardarán los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

include_directories(${BASE_FOLDER}/include)

add_library(maxstack ${BASE_FOLDER}/src/maxstack.cpp)
add_library(maxqueue ${BASE_FOLDER}/src/maxqueue.cpp)

# Crear ejecutable pila_max si existe
if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/pila_max.cpp)
    add_executable(pila_max ${BASE_FOLDER}/src/pila_max.cpp)
    target_link_libraries(pila_max maxstack)
endif()

# Crear ejecutable cola_max si existe
if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/cola_max.cpp)
    add_executable(cola_max ${BASE_FOLDER}/src/cola_max.cpp)
    target_link_libraries(cola_max maxqueue)
endif()

# Comprobación de Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else()
    message("Doxygen needs to be installed to generate documentation")
endif()

