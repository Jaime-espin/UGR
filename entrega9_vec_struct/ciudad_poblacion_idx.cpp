/**
  * @file ciudad_poblacion.cpp
  * @brief Población de un conjunto de ciudades
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que lee una lista de ciudades o regiones 
  * junto con su población y escribe un listado ordenado por ésta.
  * 
  * Para ello, deberá tener en cuenta que el listado consiste en pares 
  * "número y nombre" con las siguientes condiciones:
  *
  *    - El listado viene precedido por el número de ciudades.
  *    - En cada par de población y ciudad:
  *        - El número aparece antes del nombre.
  *        - El nombre es una palabra única, lo que permite leerla con una
  *          instrucción "cin>>nombre".
  * 
  * El resultado del programa es un total de 3 listados de las regiones, dados
  * en el siguiente orden:
  *   - ordenadas por nombre,
  *   - ordenadas por población.
  *   - orden original.
  * 
  * En la solución, debe tener en cuenta que debe cargar cada pareja en 
  * una estructura que contenga los dos datos relacionados.
  * 
  * Observe que los tres listados se deben dar en ese orden, por tanto, para
  * hacerlo podemos mantener el listado original de datos y realizar las 
  * ordenaciones con dos vectores de índices auxiliares.
  * 
  *  Para probarlo, puede introducir la población del 2021 por provincias:
      52
      Cadiz   1245960 Cantabria   584507 Castellon   587064 CiudadReal 492591
      Zamora   168725 Zaragoza   967452  Ceuta   83517 Melilla   86261
      Ourense 305223  Palencia   159123  PalmasLas   1128539 Pontevedra   944275 
      Asturias   1011792 Ávila   158421  Badajoz   669943 Baleares   1173008 
      Segovia   153663 Sevilla   1947852 Soria   88747 Tarragona   822309 
      Cordoba   776789 CoruñaLA  1120134 Cuenca   195516 Gipuzkoa   726033
      Girona   786596  Granada   921338  Guadalajara   265588 Huelva   525835 
      Madrid   6751251 Malaga   1695651  Murcia   1518486 Navarra   661537 
      Albacete  386464 Alicante  1881762 Almeria   731792 Alava   333626 
      RiojaLa   319796 Salamanca  327338 SantaCruzDeTenerife   1044405
      Teruel   134545  Toledo   709403   Valencia 2589312 Valladolid   519361 
      Barcelona 5714730 Bizkaia  1154334 Burgos   356055 Caceres   389558 
      Huesca  224264   Jaen      627190  Leon     451706 Lleida   439727 
      Lugo 326013 
  *
  */
#include <iostream>
#include <string>

using namespace std;

struct Parejas{
  int indices;
  int habitantes;
  string ciudad;
};

int main(){
  int n;
  const int MAX = 100;
  Parejas ciudades[MAX];

  cin>>n;

  for (int i = 0; i<n; i++){
    cin>>ciudades[i].ciudad>>ciudades[i].habitantes;
    ciudades[i].indices=i;
  }

  for(int i=1; i<n; i++){
    int aux=ciudades[i].indices;
    int j=i;
    while(j>0 && ciudades[aux].ciudad < ciudades[ciudades[j-1].indices].ciudad){
      ciudades[j].indices=ciudades[j-1].indices;
      j--;  
    }
    ciudades[j].indices=aux;
  }

  cout<<n<<endl;
  for(int i=0; i<n;i++){
    cout<<ciudades[ciudades[i].indices].ciudad<<" "<<ciudades[ciudades[i].indices].habitantes<<"     "<<endl;
  }
  cout <<" "<< endl;


  for(int i=1; i<n; i++){
    int aux=ciudades[i].indices;
    int j=i;
    while(j>0 && ciudades[aux].habitantes > ciudades[ciudades[j-1].indices].habitantes){
      ciudades[j].indices=ciudades[j-1].indices;
      j--;  
    }
    ciudades[j].indices=aux;
  }

  cout<<n<<endl;
  for(int i=0; i<n;i++){
    cout<<ciudades[ciudades[i].indices].ciudad<<" "<<ciudades[ciudades[i].indices].habitantes<<"     "<<endl;
  }
  cout <<" "<< endl;
  

  for(int i=1; i<n; i++){
    int aux=ciudades[i].indices;
    int j=i;
    while(j>0 && ciudades[aux].indices < ciudades[ciudades[j-1].indices].indices){
      ciudades[j].indices=ciudades[j-1].indices;
      j--;  
    }
    ciudades[j].indices=aux;
  }

  cout<<n<<endl;
  for(int i=0; i<n;i++){
    cout<<ciudades[i].ciudad<<" "<<ciudades[i].habitantes<<"     "<<endl;
  }
  cout <<" "<< endl;

}