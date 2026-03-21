#include <iostream>
#include <cstdlib>
#include "camino.h"
#include "test.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc==2){
    int opc = atoi(argv[1]);
    switch (opc){
      case 1:
        test1();
        break;
      case 2:
        test2();
        break;
      case 3:
        test3();
        break;
      case 4:
        test4();
        break;
      case 5:
        test5();
        break;
    }
    return 0;
  }
  else{
    cerr << "Error: número de argumentos incorrecto" << endl;
    cerr << "Uso: " << argv[0] << " <nº de test>" << endl;
    return 1;
  }
}

