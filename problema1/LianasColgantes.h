#ifndef P4_LIANASCOLGANTES_H
#define P4_LIANASCOLGANTES_H
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

enum Direccion {
    IZQUIERDA,
    DERECHA,
    ARRIBA,
    ABAJO
};

/**
 * @brief TDA Lianas. Representa la matriz de lianas.
 */
class Lianas {
private:

    vector<vector<int>> lianas; //matriz cuadrada de lianas
    int dimension; //dimension de matriz

public:

    /**
     * @brief Constructor con dimensión (0 por defecto).
     * @param dim Tamaño de la matriz.
     */
    explicit Lianas(int dim = 0):dimension(dim),lianas(dim,vector<int>(dim)){}
    /**
     * @brief Constructor que inicializa la matriz desde un .txt
     * @param archivo Nombre o ruta del archivo de texto.
     */
    explicit Lianas(const string& archivo);

    /**
     * @brief Getter de la dimension de la matriz
     * @return La dimension de la matriz
    */
    int getDimension() const { return dimension; }

    /**
     * @brief Sobrecarga los operadores [] el acceso a la matriz
     * @param i Índice de la fila.
     * @return Una referencia a la fila i.
     *
     * @note Es para poder acceder asi: lianas[i][j]
     */
    vector<int>& operator[](int i){ return lianas[i]; }
    /**
    * @brief Sobrecarga los operadores [] la lectura de la matriz
    * @param i Índice de la fila.
    * @return Una referencia constante a la fila i.
    *
    * @note Es para poder leer asi: lianas[i][j]
    */
    const vector<int>& operator[](int i) const { return lianas[i]; }

    /**
     * @brief Sobrecarga del operador de extracción.
     * @param is Flujo de entrada.
     * @param l Objeto Lianas a rellenar.
     * @return Referencia al flujo de entrada.
     */
    friend istream& operator>>(istream& is, Lianas& l);
};

/**
 * @brief Sobrecarga del operador de inserción.
 * @param os Flujo de salida.
 * @param l Objeto Lianas a imprimir.
 * @return Referencia al flujo de salida.
 */
ostream& operator<<(ostream& os, const Lianas& l);

/**
 * @brief TDA EstadoCamino. Representa un estado del grafo de caminos posibles
 */
class EstadoCamino {
public:
    int fila;
    int columna;
    vector<vector<bool>> visitados;  //matriz de casillas visitadas
    vector<pair<int, int>> ruta;     //recorrido actual

    /**
    * @brief Constructor de un estado
    * @param n Tamaño de la matriz de casillas visitadas y de la ruta.
    * @note Pone a la posicion (0,0) como punto de comienzo
    */
    explicit EstadoCamino(int n);
    /**
    * @brief Evalua si un salto con liana es posible en cierta direccion
    * @param l Espacio de lianas
    * @param movimiento Movimiento a evaluar
    * @return True si es posible moverse hacia la direccion de 'movimiento'
    * @return false en caso contrario
    */
    bool avanzarEstado(const Lianas& l, Direccion movimiento);
    /**
    * @brief Restaura un EstadoCamino a una fila, columna anterior
    * @param fila_anterior Fila con la que remplazar
    * @param columna_anterior Columna con la que remplazar
    */
    void deshacerEstado(int fila_anterior, int columna_anterior);
};


/**
 * @brief Calcula todas las rutas posibles hacia el altar desde el inicio del mapa de lianas y devuelve la mejor.
 * @param mapa Mapa de lianas
 * @param estado Nodo de estado actual
 * @param destino Posicion final a alcanzar
 * @param min_saltos Número de saltos minimos encontrados hacia la meta
 * @return Devuelve un vector de coordenadas con la direccion óptima.
 */
vector<pair<int,int>> caminoHaciaAltar(const Lianas& mapa, EstadoCamino& estado, pair<int,int> destino, int &min_saltos);







#endif