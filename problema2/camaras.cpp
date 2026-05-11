#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <queue> 

using namespace std;

int n;
vector<vector<int>> m;


// Fuerza Bruta
vector<int> X_fb; 
vector<int> solucion_fb;
int mejorvalor_fb = 10000;

bool Factiblefb() { 
   for (int i=0; i<n-1; i++)
      for (int j=i+1; j<n; j++)
        if (m[i][j] == 1) 
           if (X_fb[i]==0 && X_fb[j]==0) return false; 
   return true;
}

void ProcesaSolucionfb() { 
   bool essolucion = Factiblefb();
   if (essolucion) {
      int selecc = 0;
      for (int i=0; i<X_fb.size(); i++)
         if (X_fb[i]==1) selecc++;
      if (selecc < mejorvalor_fb) {
         mejorvalor_fb = selecc;
         solucion_fb = X_fb;
      }
   }
}

void fb_recursivo(int k) { 
   if (k==n) ProcesaSolucionfb();
   else {
       X_fb[k]=1; 
       fb_recursivo(k+1); 
       X_fb[k]=0; 
       fb_recursivo(k+1);
    }
}


// BACKTRACKING

int mejorvalor_va = 10000;
vector<int> solucion_va;
long long nodos_generados_va = 0;
long long nodos_podados_va = 0;


// Si estamos en k y se decide no poner cámara, verifico que no haya dejado algun pasillo hacia atrás sin vigilar
bool factible(int k, const vector<int>& X) {
    for (int i = 0; i < k; i++) {
        // Si hay pasillo y ninguno de los dos extremos tiene cámara es inviable
        if (m[i][k] == 1 && X[i] == 0 && X[k] == 0) return false;
    }
    return true;
}

void va_recursivo(int k, int camaras_colocadas, vector<int>& X) {
    // Si hay tantas o más cámaras que la mejor solución entonces podo
    if (camaras_colocadas >= mejorvalor_va) {
        nodos_podados_va++;
        return;
    }

    if (k == n) {
        if (camaras_colocadas < mejorvalor_va) {
            mejorvalor_va = camaras_colocadas;
            solucion_va = X;
        }
        return;
    }


    // Rama 1: Pongo cámara
    X[k] = 1;
    nodos_generados_va++;
    va_recursivo(k + 1, camaras_colocadas + 1, X);

    // Rama 2: NO pongo cámara
    X[k] = 0;
    nodos_generados_va++;
    if (factible(k, X)) { 
        va_recursivo(k + 1, camaras_colocadas, X);
    } else {
        nodos_podados_va++; // No es factible
    }
}


// RAMIFICACIÓN Y PODA

struct NodoB {
    vector<int> X;
    int k;
    int camaras_colocadas;
    int cota_estimada;

    // Para que priority_queue sea un min-heap
    bool operator<(const NodoB& otro) const {
        return cota_estimada > otro.cota_estimada; 
    }
};

int mejorvalor_ryp = 10000;
vector<int> solucion_ryp;
long long nodos_generados_ryp = 0;
long long nodos_podados_ryp = 0;
size_t tam_max_cola = 0;

void ryp() {
    priority_queue<NodoB> pq;
    NodoB raiz;
    raiz.X.assign(n, -1);
    raiz.k = 0;
    raiz.camaras_colocadas = 0;
    raiz.cota_estimada = 0; 
    
    pq.push(raiz);
    nodos_generados_ryp++;
    
    while(!pq.empty()) {
        if (pq.size() > tam_max_cola) tam_max_cola = pq.size();
        
        NodoB actual = pq.top();
        pq.pop();
        
        // Si la cota de este nodo ya es peor o igual a la mejor solución lo descarto
        if (actual.cota_estimada >= mejorvalor_ryp) {
            nodos_podados_ryp++;
            continue;
        }
        
        if (actual.k == n) {
            if (actual.camaras_colocadas < mejorvalor_ryp) {
                mejorvalor_ryp = actual.camaras_colocadas;
                solucion_ryp = actual.X;
            }
            continue;
        }
        
        int k = actual.k;
        
        // Hijo 1: PONER CÁMARA
        NodoB hijo1 = actual;
        hijo1.X[k] = 1;
        hijo1.k = k + 1;
        hijo1.camaras_colocadas++;
        hijo1.cota_estimada = hijo1.camaras_colocadas; // mínimo tendrá estas cámaras
        nodos_generados_ryp++;
        
        if (hijo1.cota_estimada < mejorvalor_ryp) pq.push(hijo1);
        else nodos_podados_ryp++;
        
        // Hijo 2: NO CAMARA
        NodoB hijo0 = actual;
        hijo0.X[k] = 0;
        hijo0.k = k + 1;
        hijo0.cota_estimada = hijo0.camaras_colocadas;
        nodos_generados_ryp++;
        
        if (factible(k, hijo0.X)) {
            if (hijo0.cota_estimada < mejorvalor_ryp) pq.push(hijo0);
            else nodos_podados_ryp++;
        } else {
            nodos_podados_ryp++; // Como no es factible se poda
        }
    }
}


// Funciones auxiliares
double uniforme() {
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

void generamatriz(vector<vector<int>> & matriz, int n) {
    srand(time(0));
    for (int i = 0; i < n-1; i++) 
        for (int j = i+1; j < n; j++) {
            if (uniforme() < 0.7) { 
                matriz[i][j]=0; matriz[j][i]=0;
            } else {
                matriz[i][j]=1; matriz[j][i]=1;
            }
        }
    for (int i = 0; i < n; i++) matriz[i][i]=0;
}

void generarArbol(vector<vector<int>> & matriz, int n) {
    srand(time(0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) matriz[i][j] = 0;
        
    vector<int> conectados;
    vector<int> no_conectados;
    conectados.push_back(0);
    for(int i = 1; i < n; i++) no_conectados.push_back(i);
    
    while(!no_conectados.empty()){
        int idx_c = rand() % conectados.size();
        int idx_nc = rand() % no_conectados.size();
        matriz[conectados[idx_c]][no_conectados[idx_nc]] = 1;
        matriz[no_conectados[idx_nc]][conectados[idx_c]] = 1;
        conectados.push_back(no_conectados[idx_nc]);
        no_conectados.erase(no_conectados.begin() + idx_nc);
    }
}


//main
int main(int argc, char *argv[]) {
    if (argc >= 3) {
        n = atoi(argv[1]);
        m.resize(n, vector<int>(n));
        string param2 = argv[2];
        
        if (param2 == "arbol") {
            generarArbol(m, n);
        } else {
            ifstream f(argv[2]);
            if (!f) { cout << "Archivo no valido\n"; return -1; }
            for (int i=0; i<n; i++)
                for (int j=0; j<n; j++) f >> m[i][j];
        }
    } else if (argc == 2) {
        n = atoi(argv[1]);
        m.resize(n, vector<int>(n));
        generamatriz(m, n);
    } else {
        cout << "Uso: " << argv[0] << " tamanio\n";
        return -1;
    }

    cout << "Tamano del problema: " << n << " intersecciones.\n\n";

    // FUERZA BRUTA
    if (n <= 20) { 
        X_fb.assign(n, -1);
        clock_t tantes_fb = clock();
        fb_recursivo(0);
        clock_t tdespues_fb = clock();
        cout << " FUERZA BRUTA " << endl;
        cout << "Camaras necesarias: " << mejorvalor_fb << endl;
        cout << "Tiempo: " << (double)(tdespues_fb - tantes_fb) / CLOCKS_PER_SEC << " segs.\n\n";
    }

    // BACKTRACKING
    vector<int> X_va(n, -1);
    clock_t tantes_va = clock();
    va_recursivo(0, 0, X_va);
    clock_t tdespues_va = clock();
    
    cout << " Backtracking" << endl;
    cout << "Camaras necesarias: " << mejorvalor_va << endl;
    cout << "Nodos generados: " << nodos_generados_va << endl;
    cout << "Nodos podados: " << nodos_podados_va << endl;
    cout << "Tiempo: " << (double)(tdespues_va - tantes_va) / CLOCKS_PER_SEC << " segs.\n\n";

    // RAMIFICACION Y PODA
    clock_t tantes_ryp = clock();
    ryp();
    clock_t tdespues_ryp = clock();
    
    cout << " RAMIFICACION Y PODA" << endl;
    cout << "Camaras necesarias: " << mejorvalor_ryp << endl;
    cout << "Nodos generados: " << nodos_generados_ryp << endl;
    cout << "Nodos podados: " << nodos_podados_ryp << endl;
    cout << "Tamano maximo cola prioridad: " << tam_max_cola << endl;
    cout << "Tiempo: " << (double)(tdespues_ryp - tantes_ryp) / CLOCKS_PER_SEC << " segs.\n";

    return 0;
}