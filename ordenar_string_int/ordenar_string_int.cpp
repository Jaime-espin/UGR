/**
  * @file ordenar_string_int.cpp
  * @brief Programa para ordenar dos secuencias de datos con vector de índices
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lee una secuencia de parejas nombre y número y
  * presenta las parejas con distintas ordenaciones.
  *
  * La entrada contiene datos de una votación, el nombre corresponde a un
  * partido político (no contendrá espacios blancos) y el número es un entero que
  * corresponde al número de votos.
  *
  * El formato de la entrada está compuesto por dos valores: el número de votos
  * y el nombre del partido. La lista es de tamaño indeterminado, la acabamos
  * con un primer valor entero menor que cero.
  *
  * El programa deberá:
  *    - Leer la secuencia de parejas, almacenándola en dos vectores, uno
  *      de tipo string y otro de enteros.
  *    - Declarar un vector de enteros e inicializarlo con los índices de los
  *      vectores anteriores.
  *    - Ordenar el vector de índices de forma que indique el orden de los datos
  *      introducidos ordenados por el nombre.
  *    - Listar las parejas de datos ordenados por nombre.
  *    - Ordenar el vector de índices de forma que indique el orden de los
  *      datos introducidos ordenados por el número de votos. En caso de tener
  *      el mismo número de votos, se mantiene el orden original (quedaría
  *      ordenado por nombre).
  *    - Listar las parejas de datos ordenados por número de votos.
  *    - Listar las parejas de datos en el orden de entrada.
  *
  * Los listados consisten en el número de parejas seguido por la secuencia de
  * parejas escribiendo primero el nombre del partido y después el número de votos.
  *
  * Note que el vector de string tendrá nombres sin espacios. De esa forma, la
  * solución puede leer cada string s con un simple "cin >> s", así como escribirlo
  * con un "cout << s".
  *
  * Un ejemplo de ejecución es:
      30 IZQDA    20 DRCHA    40 CENTRO    20 EXTIZQ    40 EXTDER      20 RAROS
      40 VERDES   30 ROSAS    40 GRISES    30 ALTOS     30 AZULES      30 ROJOS
      -1
      12   ALTOS 30 AZULES 30 CENTRO 40 DRCHA 20 EXTDER 40 EXTIZQ 20 GRISES 40 IZQDA 30 RAROS 20 ROJOS 30 ROSAS 30 VERDES 40
      12   DRCHA 20 EXTIZQ 20 RAROS 20 ALTOS 30 AZULES 30 IZQDA 30 ROJOS 30 ROSAS 30 CENTRO 40 EXTDER 40 GRISES 40 VERDES 40
      12   IZQDA 30 DRCHA 20 CENTRO 40 EXTIZQ 20 EXTDER 40 RAROS 20 VERDES 40 ROSAS 30 GRISES 40 ALTOS 30 AZULES 30 ROJOS 30
  *
  * donde los datos se introducen en las primeras 3 líneas (incluído el -1) y las
  * tres últimas corresponden a los tres listados.
  *
  * Otro ejemplo de ejecución es:
  *     -1
  *     No hay datos que procesar.
  *
  * donde puede ver que si la secuencia está vacía, el programa termina con un
  * mensaje indicándolo.
  * 
  * El programa deberá, además, tener una capacidad de hasta 20 pares. Si se dan más
  * de 20, deberá acabar directamente indicando que no hay capacidad, incluyendo el
  * valor de capacidad y con un mensaje final "Fin del programa".
  * 
  * Por ejemplo, la ejecución podría ser:
  *   30 IZQDA    20 DRCHA    40 CENTRO    20 EXTIZQ    40 EXTDER      20 RAROS
      40 VERDES   30 ROSAS    40 GRISES    30 ALTOS     30 AZULES      30 ROJOS
      30 IZQDA    20 DRCHA    40 CENTRO    20 EXTIZQ    40 EXTDER      20 RAROS
      40 VERDES   30 ROSAS                                                     
      40
      Error: el programa no puede continuar, capacidad (20) insuficiente.
      Fin del programa.
  *
  */
#include <iostream>
#include <string>

using namespace std;

int main(){
    const int MAX = 20;
    string partidos[MAX];
    int votos[MAX];
    int indices[MAX];
    int voto;
    int parejas=0;
    string partido;
    
    cin>>voto;
    while (voto > 0 && parejas < MAX){
        votos[parejas]=voto;
        cin>>partido;
        partidos[parejas]=partido;
        parejas++;
        indices[parejas]=parejas;

        cin>>voto;
    }
    if ( parejas>=MAX){
        cout<<"Error: el programa no puede continuar, capacidad (20) insuficiente."<<endl;
        cout<<"Fin del programa."<<endl;
    }else{

        for(int i=1; i<parejas; i++){
            int aux=indices[i];
            int j=i;
            while(j>0 && partidos[aux] < partidos[indices[j-1]]){
                indices[j]=indices[j-1];
                j--;  
            }
            indices[j]=aux;
        }

        cout<<parejas<<"    ";
        for (int i=0; i<parejas; i++){
            cout<<partidos[indices[i]]<<" "<<votos[indices[i]]<<"   ";
        }
        cout << endl;

        for(int i=1; i<parejas; i++){
            int aux=indices[i];
            int j=i;
            while(j>0 && votos[aux] < votos[indices[j-1]]){
                indices[j]=indices[j-1];
                j--;  
            }
            indices[j]=aux;
        }

        cout<<parejas<<"    ";
        for (int i=0; i<parejas; i++){
            cout<<partidos[indices[i]]<<" "<<votos[indices[i]]<<"   ";
        }
        cout << endl;


        for(int i=1; i<parejas; i++){
            int aux=indices[i];
            int j=i;
            while(j>0 && indices[aux] < indices[indices[j-1]]){
                indices[j]=indices[j-1];
                j--;  
            }
            indices[j]=aux;
        }

        cout<<parejas<<"    ";
        for (int i=0; i<parejas; i++){
            cout<<partidos[i]<<" "<<votos[i]<<"   ";
        }
        cout << endl;
    }
}