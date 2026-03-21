# Índice de Archivos

## Estructura General

```
Material para la práctica/
├── src/                           # Código fuente C++
├── scripts/                       # Scripts bash para automatización
├── docs/                          # Documentación técnica
├── datos/                         # CSV generados (salida)
├── bin/                           # Binarios compilados (generado)
└── .instructions.md               # Instrucciones para Copilot
```

---

## 📁 Carpeta `src/` - Algoritmos C++

| Archivo | Complejidad | Tipo | Descripción |
|---------|-------------|------|-------------|
| **burbuja.cpp** | O(n²) | Sorting | Ordenamiento por burbuja |
| **insercion.cpp** | O(n²) | Sorting | Ordenamiento por inserción |
| **seleccion.cpp** | O(n²) | Sorting | Ordenamiento por selección |
| **mergesort.cpp** | O(n log n) | Sorting | Merge sort (divide y vencerás) |
| **quicksort.cpp** | O(n log n) | Sorting | Quicksort (pivotes) |
| **floyd.cpp** | O(n³) | Graph | Algoritmo de Floyd (caminos más cortos) |
| **dijkstra-iterado.cpp** | O(n³) | Graph | Dijkstra iterado (Un solo origen) |
| **fibonacci.cpp** | O(2ⁿ) | Recursivo | Fibonacci recursivo simple |
| **hanoi.cpp** | O(2ⁿ) | Iterativo | Torres de Hanoi |

### Características Comunes
- Todos incluyen `#include <chrono>` para medición de tiempo
- Usan `srandom()` + `random()` (POSIX para Linux)
- Aceptan `n` como argumento de línea de comandos: `./algoritmo <n>`
- Salida CSV: `n,tiempo_en_segundos`
- **INVARIANTE**: Algoritmos originales sin modificaciones

---

## 📜 Carpeta `scripts/` - Automatización

| Script | Propósito | Uso |
|--------|-----------|-----|
| **generar_datos.sh** | Genera todos los CSV | `bash scripts/generar_datos.sh` |
| **prueba_rapida.sh** | Verifica compilación y ejecución | `bash scripts/prueba_rapida.sh` |
| **GUIA_EJECUCION.sh** | Instrucciones paso a paso | Ver en editor |

### generar_datos.sh
- Compila todos los algoritmos
- Ejecuta cada uno con rangos de `n` optimizados para su complejidad
- **Algoritmos O(n²)**: n = 10K a 250K
- **Algoritmos O(n log n)**: n = 200K a 5M
- **Algoritmos O(n³)**: n = 100 a 2.5K
- **Fibonacci**: n = 2 a 50 (pares, promediadas 3 ejecuciones)
- **Hanoi**: n = 3 a 33
- Crea carpeta `bin/` con ejecutables
- Almacena CSV en `datos/`

---

## 📚 Carpeta `docs/` - Documentación

| Archivo | Contenido |
|---------|-----------|
| **README.md** | Documentación técnica completa (~400 líneas) |
| **RESUMEN_EJECUTIVO.md** | Resumen ejecutivo con tablas |
| **VERIFICACION_FINAL.md** | Checklist de verificación |
| **INDEX.md** | Este archivo (guía de navegación) |

---

## 📊 Carpeta `datos/` - Salida (generada)

Contiene archivos CSV generados por los scripts:
- `burbuja.csv`
- `insercion.csv`
- `seleccion.csv`
- `mergesort.csv`
- `quicksort.csv`
- `floyd.csv`
- `dijkstra-iterado.csv`
- `fibonacci.csv`
- `hanoi.csv`

**Formato**: cada línea = `n,tiempo_en_segundos`

---

## 🔧 Archivos en Raíz

| Archivo | Propósito |
|---------|-----------|
| **.instructions.md** | Contexto para Copilot en VS Code |
| **ejecutar_pruebas.sh** | Script original (raíz) |
| **Guión de la Práctica 1.pdf** | Enunciado de la práctica |

---

## 🚀 Flujo Típico de Uso

### En Windows (preparación)
```bash
# Revisar archivos
ls -la src/
# Editar con VS Code
code .
```

### En Linux (ejecución)
```bash
# Prueba rápida
bash scripts/prueba_rapida.sh

# Generación completa (puede tomar minutos)
bash scripts/generar_datos.sh

# Revisar datos generados
ls -lh datos/
head datos/burbuja.csv
```

---

## ⚠️ Notas Importantes

1. **Algoritmos intactos**: Solo se añadió timing con `<chrono>`, sin modificar la lógica
2. **Dependencia de Linux**: Usa `srandom()` + `random()` que son POSIX
3. **Plataforma**: Código optimizado para ejecutar en Linux
4. **Comparabilidad**: Los datos son válidos para comparar con compañeros

---

## 📝 Resumen de Cambios Realizados

| Archivo | Cambio |
|---------|--------|
| Todos en `src/` | `+#include <chrono>` + wrapper de timing |
| Todos en `src/` | Salida agregada: `cout << n << "," << tiempo << endl;` |
| Compilación | Añadido flag `-O2` para optimización |

---

*Última actualización: Marzo 2026*
