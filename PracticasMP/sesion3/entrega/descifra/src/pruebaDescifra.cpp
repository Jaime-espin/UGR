/*
 PROGRAMA PARA PRUEBAS DEL MÓDULO DESCIFRA
 
 NO MODIFICAR EL CÓDIGO
 
 
 
 */

#include <iostream>
#include "descifra.h"

using namespace std;

void lee_linea(char c[], const int tam) {
  do {
    cin.getline(c, tam);
  } while (c[0] == '\0');
}

void prettyPrint(const char c[]) {
  int i = 0;
  while (c[i] != '\0') {
    if (c[i] == ' ')
      cout << '_';
    else
      cout << c[i];
    ++i;
  }
}

const int TAM_MAX = 1000;

int main() {
  
  char frase[TAM_MAX];
  char codigo[TAM_MAX];
  int nCads = 0;
  int tam;
  
  cout << "Introduce el número de cadenas a procesar: ";
  cin >> nCads;
  cout << "Cadenas a procesar: " << nCads << endl;
  
  for (int i=0; i<nCads; ++i) {
    cout << endl;
    lee_linea(frase, TAM_MAX);
    tam = longitudCad(frase);
    prettyPrint(frase);
    cout << " tiene " << tam << " caracteres" << endl;
    descifra(frase, codigo);
    cout << "Código -> " << codigo << endl;
  }
  
  return (0);
}
