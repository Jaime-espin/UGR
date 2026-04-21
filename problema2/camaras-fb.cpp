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
bool quedanPasillosSinVigilar(vector<vector<int>> m){
//Recorrer la matriz. Si encuentra al menos un 1 (un pasillo sin vigilar),
// devuelve true. Si revisa toda la matriz y son todo ceros, devuelve false.
}

//devuelve el índice de la intersección elegida
int verticeMayorGrado(vector<vector<int>> m, int n){

}

//Ir a la fila y a la columna correspondientes a esa intersección 
//y poner todos sus valores a 0. Esto "borra" los pasillos de la matriz, 
//simulando que ya están vigilados.
void marcarPasillosVigilados(vector<vector<int>> &m, int indice){

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

   }

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
//////////////////

int main (int argc, char *argv[]){

   if(argc == 3){
      n = atoi(argv[1]);
      m.resize(n);
      for (int i=0; i<n; i++) m[i].resize(n);
   //////////////////lectura del fichero
      ifstream f (argv[2]);
      if (!f){
         cout << "Archivo no valido" << endl;
         return -1;
      }
      m.resize(n);
      for (int i=0; i<n; i++) m[i].resize(n);
      int l=0;
      while (!f.eof()){
         for (int j=0;j<n; j++) f >> m[l][j];
         l++;
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

   clock_t tantes;
   clock_t tdespues;
   X.resize(n);
   solucion.resize(n);
   for (int i=0; i<n; i++)
      X[i] = -1; //-1 significa no asignado aun, ni pongo camara ni no pongo camara
   tantes = clock();
   fb_recursivo(0);
   tdespues = clock();
   cout<<"La solucion con valor "<<mejorvalor<<" es:"<<endl;
   MuestraSolucion();
   cout << n << " tiempo: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
   return 0;
}
