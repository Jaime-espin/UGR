#include <iostream>
#include "lienzo.h"
#include "test.hpp"

using namespace std;

void guion();

int main(int argc, char* argv[]) {
  
  if (argc != 2){
    cerr << "Error: número de argumentos incorrecto" << endl;
    cerr << "Uso: " << argv[0] << " <nº de test> " << endl;
    return(1);
  }
  else{
    int opcion = atoi(argv[1]);
    switch (opcion){
      case 0:
        guion();
        break;
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
      case 6:
        test6();
        break;
      case 7:
        test7();
        break;
      case 8:
        test8();
        break;
    }
    return 0;
  }
}

void guion(){
  Lienzo l;
  reservarLienzo(l, 5, 7);
  rellenarLienzo(l, '@');
  dibujarRectangulo(l, 1, 1, 3, 3, 'X');
  imprimirLienzo(l);
  cout << endl;
  rellenarLienzo(l, '@');
  dibujarRectangulo(l, 3, 3, 3, 3, 'X');
  imprimirLienzo(l);
  cout << endl;
  rellenarLienzo(l, '@');
  dibujarRectangulo(l, -1, -1, 3, 3, 'X');
  imprimirLienzo(l);
  cout << endl;
  
  
  rellenarLienzo(l, '@');
  dibujarRectangulo(l, 0, 0, 1, 6, '1');
  dibujarRectangulo(l, 0, 6, 5, 1, '2');
  imprimirLienzo(l);
  cout << endl;
  rotarLienzo(l);
  imprimirLienzo(l);
  cout << endl;
  rotarLienzo(l);
  imprimirLienzo(l);
  cout << endl;
  
  liberarLienzo(l);
  
  Lienzo l1, l2, l3;
  reservarLienzo(l1, 5, 4);
  rellenarLienzo(l1, '-');
  dibujarRectangulo(l1, 0, 0, 2, 2, '@');
  
  reservarLienzo(l2, 5, 7);
  rellenarLienzo(l2, '*');
  dibujarRectangulo(l2, 2, 2, 3, 1, '+');
  
  unirLienzos(l3, l1, l2);
  
  imprimirLienzo(l1);
  cout << endl;
  imprimirLienzo(l2);
  cout << endl;
  imprimirLienzo(l3);
  cout << endl;
  
  liberarLienzo(l1);
  liberarLienzo(l2);
  liberarLienzo(l3);
  
  reservarLienzo(l, 6, 6);
  rellenarLienzo(l, '@');
  dibujarRectangulo(l, 1, 1, 4, 4, 'X');
  imprimirLienzo(l);
  cout << endl;
  
  copiarRectangulo(l1, l, 0, 0, 3, 3);
  imprimirLienzo(l1);
  cout << endl;
  
  copiarRectangulo(l2, l, 1, 1, 4, 3);
  imprimirLienzo(l2);
  cout << endl;
  
  copiarRectangulo(l3, l, 3, 3, 6, 6);
  imprimirLienzo(l3);
  cout << endl;
  
  liberarLienzo(l);
  liberarLienzo(l1);
  liberarLienzo(l2);
  liberarLienzo(l3);
}
