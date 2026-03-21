/**
  * @file cambio.cpp
  * @brief Tabla de cambio entre dólar y euros
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que muestre una tabla de conversión entre dólares y 
  * euros. Para ello, el programa pedirá desde la entrada estándar el cambio 
  * de moneda en curso (cuántos euros vale un dólar) y el número de dólares
  * para los que se desea tener la conversión. Utilice un bucle de tipo for
  * para resolver el problema.
  * 
  * Una posible ejecución sería la siguiente:
  * 
  *      ¿Cuántos euros vale un dólar? 0.733
  *      ¿Límite de cambio? 12
  *      Tabla de cambio:
  *      1 $ = 0.733 e
  *      2 $ = 1.466 e
  *      3 $ = 2.199 e
  *      4 $ = 2.932 e
  *      5 $ = 3.665 e
  *      6 $ = 4.398 e
  *      7 $ = 5.131 e
  *      8 $ = 5.864 e
  *      9 $ = 6.597 e
  *      10 $ = 7.33 e
  *      11 $ = 8.063 e
  *      12 $ = 8.796 e
  *      Fin de la tabla
  * 
  * En la ejecución, un valor menor que 1 como límite debería dar una tabla
  * vacía:
  *      ¿Cuántos euros vale un dólar? 0.733
  *      ¿Límite de cambio? -6
  *      Tabla de cambio:
  *      Fin de la tabla
  * 
  */
#include <iostream>

using namespace std;

int main() {
    double cambio;
    int limite;

    cout << "Cuántos euros vale un dólar? ";
    cin >> cambio;

    cout << "¿Límite de cambio? ";
    cin >> limite;

    cout << "Tabla de cambio:" << endl;
    for (int i = 1; i <= limite; i++) {
        cout << i << " $ = " << i * cambio << " e" << endl;
    }
    cout << "Fin de la tabla" << endl;

    return 0;
}