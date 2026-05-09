#include <iostream>
#include "LianasColgantes.h"

using namespace std;

int main(const int argc, const char * argv[]) {

    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <archivo_matriz.txt>" << endl;
        return -1;
    }

    fstream archivo;
    archivo.open(argv[1]);
    if (!archivo) {
        cerr << "Error al abrir archivo." << endl;
        return -1;
    }

    //Inicalizamos matriz
    Lianas lianas;
    archivo >> lianas;

    cout << endl << "Matriz Inicial:\n" << lianas;

    return 0;
}