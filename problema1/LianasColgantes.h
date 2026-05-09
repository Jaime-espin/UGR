#ifndef P4_LIANASCOLGANTES_H
#define P4_LIANASCOLGANTES_H
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief TDA Lianas. Representa la matriz de lianas.
 */
class Lianas {
private:

    vector<vector<int>> lianas; //matriz cuadrada de lianas
    int dimension; //dimension de matriz

    /**
     * @brief Método privado para la exploración usando recursividad
    */    
    void explorar(int x, int y, int destinoX, int destinoY, vector<vector<bool>>& visitado,
         vector<pair<int, int>>& camino_actual, vector<pair<int, int>>& mejor_camino, int& min_saltos) const;

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

    /** 
     * @brief Método que resuelve el problema
    */
    void resolver(int destinoX, int destinoY, int& minSaltos, vector<pair<int, int>>& mejorCamino) const;
};

/**
 * @brief Sobrecarga del operador de inserción.
 * @param os Flujo de salida.
 * @param l Objeto Lianas a imprimir.
 * @return Referencia al flujo de salida.
 */
ostream& operator<<(ostream& os, const Lianas& l);





#endif