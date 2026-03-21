# AUTOMATIZACIÓN DE RECOPILACIÓN DE DATOS - PRÁCTICA DE ALGORÍTMICA

## Descripción

Este conjunto de herramientas automatiza la recopilación de datos de rendimiento para algoritmos implementados en C++. Los datos se guardan en archivos CSV listos para importar en Excel.

## Archivos Modificados

### Algoritmos de Ordenación (C++)
- **burbuja.cpp** - Algoritmo cuadrático O(n²)
- **insercion.cpp** - Algoritmo cuadrático O(n²)
- **seleccion.cpp** - Algoritmo cuadrático O(n²)
- **mergesort.cpp** - Algoritmo O(n log n)
- **quicksort.cpp** - Algoritmo O(n log n)

### Algoritmos de Grafos (C++)
- **floyd.cpp** - Algoritmo cúbico O(n³)
- **dijkstra-iterado.cpp** - Algoritmo cúbico O(n³)

### Otros Algoritmos (C++)
- **fibonacci.cpp** - Secuencia de Fibonacci (exponencial)
- **hanoi.cpp** - Torre de Hanoi (exponencial)

### Script de Automatización
- **generar_datos.sh** - Script Bash que compila y ejecuta todos los algoritmos

## Cambios Realizados en los Archivos C++

### 1. Inclusión de <chrono>
Todos los archivos ahora incluyen la librería `<chrono>` para medición de tiempo de alta precisión.

### 2. Medición de Tiempo
Cada programa mide el tiempo de ejecución del algoritmo principal de forma automática:

```cpp
auto inicio = chrono::high_resolution_clock::now();
// ... algoritmo ...
auto fin = chrono::high_resolution_clock::now();

chrono::duration<double> duracion = fin - inicio;
double tiempo = duracion.count();
```

### 3. Salida Formateada
La salida estándar imprime ÚNICAMENTE dos valores separados por coma:

```
n,tiempo_en_segundos
```

**Ejemplo:** `100000,0.0098676`

### 4. Entrada por Línea de Comandos
Todos los programas aceptan el tamaño/parámetro como primer argumento:

```bash
./program n
```

## Cómo Usar

### Método 1: Script Automatizado (Recomendado)

En Git Bash o terminal compatible con Bash:

```bash
chmod +x generar_datos.sh
./generar_datos.sh
```

El script:
- Compila todos los programas con optimización `-O2`
- Ejecuta cada algoritmo con los rangos especificados
- Genera archivos CSV con la siguienteestructura

### Método 2: Compilación Manual

Para compilar un algoritmo individual:

```bash
g++ -O2 -o burbuja_bin burbuja.cpp
```

Para ejecutar con tamaño n:

```bash
./burbuja_bin 50000
```

## Rangos y Ciclos de Ejecución

| Categoría | Algoritmos | Rango | Incremento | K* |
|-----------|-----------|-------|-----------|-----|
| Cuadráticos | Burbuja, Inserción, Selección | 10,000 - 250,000 | 10,000 | 1 |
| N log N | Mergesort, Quicksort | 200,000 - 5,000,000 | 200,000 | 1 |
| Cúbicos | Floyd, Dijkstra | 100 - 2,500 | 100 | 1 |
| Exponencial | Fibonacci | 2 - 50 (pares) | 2 | 3 |
| Exponencial | Hanoi | 3 - 33 | 1 | 1 |

**K* = Número de ejecuciones para promediar (solo Fibonacci)

## Archivos de Salida

El script genera automáticamente los siguientes archivos CSV:

1. **burbuja_resultados.csv** - Datos de Burbuja
2. **insercion_resultados.csv** - Datos de Inserción
3. **seleccion_resultados.csv** - Datos de Selección
4. **mergesort_resultados.csv** - Datos de Mergesort
5. **quicksort_resultados.csv** - Datos de Quicksort
6. **floyd_resultados.csv** - Datos de Floyd
7. **dijkstra_resultados.csv** - Datos de Dijkstra
8. **fibonacci_resultados.csv** - Datos de Fibonacci (promediados)
9. **hanoi_resultados.csv** - Datos de Hanoi

### Formato de los CSV

Cada archivo tiene la siguiente estructura:

```
Tamaño,Tiempo
10000,0.000123
20000,0.000456
...
```

La primera columna es el tamaño de entrada, la segunda es el tiempo en segundos (punto flotante).

## Importar en Excel

1. Abrir Excel
2. Menú: Datos → Obtener datos externos → Desde texto
3. Seleccionar uno de los archivos `.csv`
4. Usar coma como delimitador
5. Los datos estarán listos para gráficos

## Compilador Requerido

- **g++** (GCC) versión 5.0 o superior
- En Windows: MinGW-w64 o equivalente
- En Linux/macOS: g++ estándar

### Verificar Versión

```bash
g++ --version
```

## Notas Importantes

1. **Precisión de Tiempo**: Se usa `std::chrono::high_resolution_clock` para máxima precisión (microsegundos)

2. **Optimización -O2**: El script compila con `-O2` para aprovechar optimizaciones del compilador

3. **Compatibilidad Windows**: El script usa `seq` en lugar de `{inicio..fin..paso}` para máxima compatibilidad

4. **Fibonacci**: Se ejecuta 3 veces por cada n y se promedian los resultados (muy rápido para valores pequeños)

5. **Hanoi**: Se desactiva la salida de movimientos para medir solo el tiempo de computación

6. **Generación de Datos**: Todos los programas usan `srand(time(0))` para generar datos aleatorios diferentes en cada ejecución

## Ejemplo de Ejecución

```bash
$ ./generar_datos.sh

=== Compilando algoritmos con optimización -O2 ===
Compilacion completada.

=== Ejecutando algoritmos cuadraticos (Burbuja, Insercion, Seleccion) ===
✓ burbuja_resultados.csv generado
✓ insercion_resultados.csv generado
✓ seleccion_resultados.csv generado

...
```

## Solucionar Problemas

### Error: "g++: command not found"
Instalar GCC/MinGW o ejecutar desde Git Bash (en Windows)

### Error: "./generar_datos.sh: permission denied"
Ejecutar `chmod +x generar_datos.sh`

### Los CSV están vacíos
Verificar que los binarios se compilaron correctamente compilando uno manualmente

### El formato de salida es incorrecto
Verificar que el programa imprime exactamente: `n,tiempo` sin espacios

## Contacto y Soporte

Para preguntas sobre la implementación, verificar que:
- Los archivos .cpp incluyen `#include <chrono>`
- La salida es exactamente `n,tiempo_en_segundos`
- Se compila con `g++ -O2`

---

**Última actualización**: Marzo 2026
**Formato recomendado para Excel**: CSV
