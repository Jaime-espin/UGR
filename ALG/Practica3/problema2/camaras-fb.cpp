#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>

//algoritmo de fuerza bruta para el problema de las cámaras de vigilancia

int n;
vector<vector<int> > m; //matriz de adyacencia del grafo
//Si m[i][j]=1 hay un pasillo entre la instersección i y j
vector<int> X; //Se guarda lo que prueba el algoritmo, 1 hay camara, 0 no hay y -1 no decidido
vector<int> solucion;
int mejorvalor = 10000;

bool Factiblefb(){ //Recorre la matriz buscando pasillos reales
   for (int i=0; i<n-1; i++)
      for (int j=i+1; j<n; j++)
        if (m[i][j] == 1) //existe la arista
           if (X[i]==0 && X[j]==0) return false; //Si hay un pasillo donde ninguno de sus dos extremos tiene cámara, la combinación actual no sirve
   return true;
}

void ProcesaSolucionfb() { //Cuenta cuantas cámaras tiene la solución, si es la mejor la guarda
   bool essolucion = Factiblefb();
   if (essolucion) {
      int selecc = 0;
      for (int i=0; i<X.size(); i++)
         if (X[i]==1) selecc++;
      if (selecc < mejorvalor) {
         mejorvalor = selecc;
         solucion = X;
      }
   }
}

void MuestraSolucion(){
   for (int i=0; i<solucion.size(); i++)
        cout<<solucion[i]<<" ";
   cout<<endl;
}

void fb_recursivo(int k){ //genera todas las combinaciones posibles de poner y no poner cámaras.
   if (k==n) ProcesaSolucionfb();
   else {
       X[k]=1; //pongo cámara en interseccion k
       fb_recursivo(k+1); //llama a la recursividad para la siguiente intersección
       X[k]=0; //no pongo cámara en interseccion k
       fb_recursivo(k+1);
    }
}

//////////////////
//Solución greedy

//Para condición de parada
bool quedanPasillosSinVigilar(vector<vector<int>> mapa){
//Recorrer la matriz. Si encuentra al menos un 1 (un pasillo sin vigilar),
// devuelve true. Si revisa toda la matriz y son todo ceros, devuelve false.
   for (int i=0; i<n-1; i++)
      for (int j=i+1; j<n; j++)
        if (mapa[i][j] == 1) return true;
   return false;
}

//devuelve el índice de la intersección elegida
int verticeMayorGrado(vector<vector<int>> mapa){
   int max_grado_encontrado = 0;
   int indice_ganador;

   for(int i=0; i<n; i++){
      int contador_pasillos = 0;
      for(int j = 0; j<n; j++){
         if(mapa[i][j]==1) contador_pasillos++;
      }
      if(contador_pasillos>max_grado_encontrado){
         max_grado_encontrado = contador_pasillos;
         indice_ganador=i;
      }
   }
   return indice_ganador;
}

//Ir a la fila y a la columna correspondientes a esa intersección 
//y poner todos sus valores a 0. Esto "borra" los pasillos de la matriz, 
//simulando que ya están vigilados.
void marcarPasillosVigilados(vector<vector<int>> &mapa, int indice){
   for(int i=0; i<n; i++){
      mapa[indice][i]=0;
      mapa[i][indice] = 0;
   }
}
//El procedimiento es que se debe buscar el lugar con mayor intersección de pasillos
//En ese lugar se colocará la cámara y así sucesivamente. Buscamos el vertice con mayor grado.
//Cuando coloquemos una camara eliminemos los pasillos del grafo a los que vigila esta
//nueva camara para que no interfiera en el resto de decisiones.
//Si no entendeis el planteamiento me podeis preguntar ;)
void greedy(){
   vector<vector<int>> aux = m; //Lo copiamos para no perder la info original
   vector<int> intersecciones; //Donde guardaremos las intersecciones con camara
   
   while(quedanPasillosSinVigilar(aux)){
      int mayor_grado = verticeMayorGrado(aux);
      intersecciones.push_back(mayor_grado);
      marcarPasillosVigilados(aux, mayor_grado);
   }

   cout<<"Seran necesarias "<<intersecciones.size()<<" cámaras"<<endl;
}

//Esta función busca una hoja y devuelve a su nodo padre
int BuscamosHoja(vector<vector<int>> &mapa){
   for(int i = 0; i<n; i++){//Buscamos hojas
      int grado = 0;
      int padre = -1;
      for(int j = 0; j<n; j++){
         if(mapa[i][j]==1){
            grado++; 
            padre=j;
         }
      }
      if(grado==1) return padre; //Hoja encontrada
   }
   return -1;
}

//(Opcional) Algoritmo voraz para encontrar la solución optima para arboles.
//El procedimiento consistirá en buscar los callejones sin salida (hojas)
//Y colocar la camara en el nodo padre de estas intersecciones.
void greedyArbol(){
   vector<vector<int>> aux = m; //Lo copiamos para no perder la info original
   vector<int> intersecciones; //Donde guardaremos las intersecciones con camara
   
   while(quedanPasillosSinVigilar(aux)){
      int padre_hoja=BuscamosHoja(aux);
      if(padre_hoja == -1) break;
      intersecciones.push_back(padre_hoja);
      marcarPasillosVigilados(aux, padre_hoja);
   }
   cout << "Solucion OPTIMA para ARBOL: Seran necesarias " << intersecciones.size() << " camaras." << endl;
}


/////////////// Para generar grafos aleatoriamente
double uniforme() //Genera un número uniformemente distribuido en el intervalo [0,1) 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void generamatriz(vector<vector<int> > & matriz, int n) {
 srand(time(0));
 for (int i = 0; i < n-1; i++) //esta forma es para una matriz simetrica
   for (int j = i+1; j < n; j++) {
        double u=uniforme();
        if (u<0.7) { //pongo aristas con probabilidad 0.3
           matriz[i][j]=0;
           matriz[j][i]=0;
        }
        else {
           matriz[i][j]=1;
           matriz[j][i]=1;
        }
     }
 for (int i = 0; i < n; i++) matriz[i][i]=0;
}

//Para generar arboles
void generarArbol(vector<vector<int> > & matriz, int n){
   srand(time(0));
   // 1. Primero, nos aseguramos de que la matriz esté completamente a 0
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matriz[i][j] = 0;
        }
    }
    
    vector<int> conectados;
    vector<int> no_conectados;
    
    // 2. Empezamos con el nodo 0 en el árbol
    conectados.push_back(0);
    
    // 3. El resto de nodos (1 a n-1) están fuera del árbol inicialmente
    for(int i = 1; i < n; i++){
        no_conectados.push_back(i);
    }
    
    // 4. Vamos uniendo nodos uno a uno hasta que todos estén en el árbol
    while(!no_conectados.empty()){
        // Elegimos un nodo aleatorio de los que YA están en el árbol
        int indice_conectado = rand() % conectados.size();
        int nodo_u = conectados[indice_conectado];
        
        // Elegimos un nodo aleatorio de los que AÚN NO están en el árbol
        int indice_no_conectado = rand() % no_conectados.size();
        int nodo_v = no_conectados[indice_no_conectado];
        
        // Creamos el pasillo (arista) entre ellos en la matriz
        matriz[nodo_u][nodo_v] = 1;
        matriz[nodo_v][nodo_u] = 1;
        
        // Añadimos el nuevo nodo a la lista de conectados
        conectados.push_back(nodo_v);
        
        // Lo borramos de la lista de no conectados
        no_conectados.erase(no_conectados.begin() + indice_no_conectado);
    }
}
//////////////////

int main (int argc, char *argv[]){
   bool es_arbol = false;
   if(argc > 1 && string(argv[argc-1]) == "arbol"){
       es_arbol = true;
   }
   if(argc >= 3){
      n = atoi(argv[1]);
      m.resize(n);
      for (int i=0; i<n; i++) m[i].resize(n);
   //////////////////lectura del fichero
      ifstream f (argv[2]);
      string parametro2 = argv[2]; // Guardamos el segundo parámetro
        
      if(parametro2 == "arbol"){
         // Generamos un árbol
         generarArbol(m, n);
         es_arbol = true;
      } else {
         // Lectura del fichero (tu código original)
         ifstream f (argv[2]);
         if (!f){
            cout << "Archivo no valido" << endl;
            return -1;
         }
         int l=0;
         while (!f.eof()){
            for (int j=0;j<n; j++) f >> m[l][j];
            l++;
         }
      }
   ////////////////////////////
   }
   else if(argc == 2) {
      n = atoi(argv[1]);
      m.resize(n);
      for (int i=0; i<n; i++) m[i].resize(n);
      generamatriz(m,n);
   }
   else {
      cout << argv[0] << " tamanio " << "fichero"<<endl;
      cout << "O "<<argv[0] << " tamanio " <<endl;
      return -1;
   }

   cout<<"La matriz de adyacencia del grafo es:"<<endl;
   for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++)
            cout<<m[i][j]<<" ";
      cout<<endl;
   }
   // 1. Ejecución de Fuerza Bruta (Original del profe)
   clock_t tantes;
   clock_t tdespues;
   X.resize(n);
   solucion.resize(n);
   for (int i=0; i<n; i++)
      X[i] = -1; 
   tantes = clock();
   fb_recursivo(0);
   tdespues = clock();
   cout << "\n--- Fuerza Bruta ---" << endl;
   cout << "La solucion con valor " << mejorvalor << " es:" << endl;
   MuestraSolucion();
   cout << "Tiempo FB: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << " segs.\n" << endl;

   // 2. Ejecución del Algoritmo Voraz General (Para todo tipo de grafos)
   cout << "--- Algoritmo Voraz (Nodo con mayor grado) ---" << endl;
   clock_t tantes_v = clock();
   greedy();
   clock_t tdespues_v = clock();
   cout << "Tiempo Voraz: " << (double)(tdespues_v - tantes_v) / CLOCKS_PER_SEC << " segs.\n" << endl;

   // 3. Ejecución del Algoritmo Voraz de Árboles (SOLO si hemos generado un árbol)
   if (es_arbol) {
      cout << "--- Algoritmo Voraz OPTIMO para Arboles ---" << endl;
      clock_t tantes_a = clock();
      greedyArbol();
      clock_t tdespues_a = clock();
      cout << "Tiempo Voraz Arbol: " << (double)(tdespues_a - tantes_a) / CLOCKS_PER_SEC << " segs.\n" << endl;
   }

   return 0;
}
