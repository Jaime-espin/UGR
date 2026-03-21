#ifndef __CIFRAS_SET_H__
#define __CIFRAS_SET_H__

#include <vector>
#include <string>
#include <set>

using namespace std;

int C[14]={1,2,3,4,5,6,7,8,9, 10, 25, 50, 75, 100};

/**
 * @brief Clase que representa el juego de las cifras
 * 
 * Esta clase implementa el juego de las cifras, donde el objetivo es alcanzar
 * un número objetivo utilizando operaciones aritméticas básicas (+, -, *, /)
 * con un conjunto de números dados.
 * 
 * El algoritmo busca todas las combinaciones posibles de operaciones entre
 * los números disponibles mediante backtracking recursivo hasta encontrar
 * una solución exacta o la aproximación más cercana.
 */
class Cifras{
    private:
    int valor_actual;
    multiset<int> numeros_restantes;
    int objetivo;

    vector<string> operaciones;

    int mejor_resultado_encontrado;

    public:
    /**
     * @brief Constructor por defecto de la clase Cifras
     */
    Cifras();

    /**
     * @brief Imprime las operaciones realizadas para llegar a la solución
     */
    void imprimirOperaciones();

    /**
     * @brief Obtiene el mejor resultado encontrado durante la búsqueda
     * 
     * @return int El resultado más cercano al objetivo encontrado
     */
    int get_mejor_resultado_encontrado();

    /**
     * @brief Resuelve el juego de cifras para un conjunto de números y un objetivo dados
     * @param numeros_iniciales Multiset con los números disponibles para realizar operaciones
     * @param target Número objetivo que se intenta alcanzar
     * @return true si se encontró una solución exacta, false en caso contrario
     */
    bool resolver_juego(const multiset<int>& numeros_iniciales, int target);

    private:
    /**
     * @brief Método recursivo que busca una solución al juego mediante backtracking
     * @param restantes Multiset con los números disponibles en este paso de la recursión
     * @param objetivo Número objetivo que se intenta alcanzar
     * @return true si se encontró una solución exacta, false en caso contrario
     */
    bool buscar_solucion(multiset<int> restantes, int objetivo);
};

#endif
