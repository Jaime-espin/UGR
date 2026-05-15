#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Calcula la combinación de compra óptima teniendo en cuenta la oferta 2x3.
 * @param dinero_disponible Dinero máximo.
 * @param n_productos Número de productos.
 * @param precio Vector de precios por producto.
 * @param beneficio Vector de beneficios por unidad de producto.
 * @return Vector de pares {índice_producto, cantidad} con la solución óptima.
 */
vector<pair<int, int>> mejorCombinacionCompra(int dinero_disponible, const int n_productos, const vector<int>& precio, const vector<int>& beneficio);

/**
 * @brief Reconstruye la solución trazando hacia atrás la tabla.
 * @note Es solo una funcion auxiliar al algoritmo de programacion dinamica
 *
 * @param tabla Tabla calculada por mejorCombinacionCompra.
 * @param dinero_disponible Presupuesto máximo.
 * @param n_productos Número de productos.
 * @param precio Vector de precios por producto.
 * @param beneficio Vector de beneficios por unidad de producto.
 * @return Vector de pares {índice_producto, cantidad} con los productos seleccionados.
 */
vector<pair<int,int>> construirSolucion(const vector<vector<int>> &tabla, int dinero_disponible, const int n_productos, const vector<int>& precio, const vector<int>& beneficio);

int main(const int argc, const char * argv[]) {

    int n = 3;
    int dineros = 10;
    vector<int> precio = {3, 4, 5};
    vector<int> beneficio = {7, 8, 9};

    vector<pair<int,int>> solucion = mejorCombinacionCompra(dineros,n, precio, beneficio);

    cout << "COMPRA OPTIMA 1" << endl << endl;
    for (int i = 0; i < solucion.size(); i++)
        cout << "Producto " << solucion[i].first << ": " << solucion[i].second << " unidad(es)." << endl;


    precio.erase(precio.begin(), precio.end());
    beneficio.erase(beneficio.begin(), beneficio.end());
    solucion.erase(solucion.begin(), solucion.end());


    n = 6;
    dineros = 16;
    precio = {1,2,3,4,5,6};
    beneficio = {7,8,9,5,6,18};
    solucion = mejorCombinacionCompra(dineros,n, precio, beneficio);

    cout << endl << "COMPRA OPTIMA 2" << endl << endl;
    for (int i = 0; i < solucion.size(); i++)
        cout << "Producto " << solucion[i].first << ": " << solucion[i].second << " unidad(es)." << endl;

    return 0;
}


vector<pair<int, int>> mejorCombinacionCompra(int dinero_disponible, const int n_productos,
                                              const vector<int> &precio, const vector<int> &beneficio) {

    //Matriz de n_productos+1 filas y dinero_disponible+1 columnas inicializada a 0
    vector<vector<int>> tabla(n_productos + 1, vector<int>(dinero_disponible + 1, 0));

    for (int i = 1; i <= n_productos; i++) {
        for (int k = 1; k <= dinero_disponible; k++) {

            int p_actual = precio[i-1];
            int beneficio_actual = beneficio[i-1];

            if (p_actual <= k) { //si hay plata para al menos 1

                int no_comprar = tabla[i-1][k];
                int comprar_uno = tabla[i-1][k-p_actual] + beneficio_actual;
                int comprar_dos = (2 * p_actual <= k) ? tabla[i-1][k - 2 * p_actual] + 3 * beneficio_actual : 0 ;

                tabla[i][k] = max({no_comprar, comprar_uno, comprar_dos});

            } else //si no hay plata
                tabla[i][k] = tabla[i-1][k];
        }
    }

    //Construimos solucion
    return construirSolucion(tabla, dinero_disponible, n_productos, precio, beneficio);
}

vector<pair<int,int>> construirSolucion(const vector<vector<int>> &tabla, int dinero_disponible, const int n_productos,
                                        const vector<int>& precio, const vector<int>& beneficio) {

    vector<pair<int, int>> compras; // par {indice_producto, cantidad}

    for (int i = n_productos; i > 0 && dinero_disponible > 0; --i) {

        const int p = precio[i-1];
        const int b = beneficio[i-1];

        // si valor viene de la celda de arriba subimos en la tabla
        if (tabla[i][dinero_disponible] == tabla[i-1][dinero_disponible])
            continue;

        // el valor viene con la oferta 3x2
        else if (2 * p <= dinero_disponible and tabla[i][dinero_disponible] == tabla[i-1][dinero_disponible - 2 * p] + 3 * b) {

            compras.emplace_back(i, 3); //metemos 3 unidades del producto en el carrito
            dinero_disponible -= 2 * p;

        } else { //si solo va a comprar 1 unidad del producto
            compras.emplace_back(i, 1);
            dinero_disponible -= p;
        }
    }

    return compras;
}