# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++20 -pedantic -Wall

# Directorio de salida y nombre del ejecutable
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

# Archivos fuente
SRCS = main.cpp practica2.cpp

# Archivos objeto (convierte la lista de .cpp a .o dentro de build/)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Regla principal (lo que se ejecuta al escribir "make")
all: $(TARGET)

# Regla para enlazar el ejecutable final
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para compilar cada .cpp en un archivo .o
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para crear la carpeta build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla para limpiar el proyecto (ejecutar con "make clean")
clean:
	rm -rf $(BUILD_DIR)

run: 
	@echo "Compilando..."
	./$(BUILD_DIR)/main
	@echo "Generando imagenes"
	gnuplot graficar_individuales.gnuplot
	gnuplot graficar_comparacion.gnuplot

# Evita conflictos si hay archivos que se llamen "all" o "clean"
.PHONY: all clean