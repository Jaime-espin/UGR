#include <iostream>
#include <cassert>
#include "lienzo.h"
#include "test.hpp"

using namespace std;

void mostrarCartel(string s){
  cout << endl << "*************************************" << endl;
  cout << "  " << s;
  cout << endl << "*************************************" << endl;
}


void test1(){
  mostrarCartel("Prueba Reserva/Liberación");
  
  Lienzo imgBase;
  reservarLienzo(imgBase, 10, 10);
  liberarLienzo(imgBase);
  
  liberarLienzo(imgBase);
  
  Lienzo img2;
  liberarLienzo(img2);
  reservarLienzo(img2, 5, 5);
  liberarLienzo(img2);
}



void test2(){
  mostrarCartel("Prueba dibujaRectangulo()");
  Lienzo imgBase;
  reservarLienzo(imgBase, 5, 7);
  rellenarLienzo(imgBase, '@');
  
  dibujarRectangulo(imgBase, 1, 1, 3, 3, 'X');
  imprimirLienzo(imgBase);
  
  rellenarLienzo(imgBase, '@');
  
  dibujarRectangulo(imgBase, 3, 3, 3, 3, 'X');
  imprimirLienzo(imgBase);
  
  rellenarLienzo(imgBase, '@');
  
  dibujarRectangulo(imgBase, -1, -1, 3, 3, 'X');
  imprimirLienzo(imgBase);
  
  liberarLienzo(imgBase);
}

void test3(){
  mostrarCartel("Prueba sonIguales()");
  Lienzo img1, img2;
  reservarLienzo(img1, 5, 6);
  rellenarLienzo(img1, '.');
  reservarLienzo(img2, 5, 6);
  rellenarLienzo(img2, '.');
  assert(sonIguales(img1, img2));
  
  rellenarLienzo(img1, '*');
  assert(!sonIguales(img1, img2));
  
  rellenarLienzo(img1, '.');
  dibujarRectangulo(img1, 2, 3, 2, 3, '*');
  assert(!sonIguales(img1, img2));
  
  liberarLienzo(img1);
  reservarLienzo(img1, 5, 7);
  rellenarLienzo(img1, '.');
  assert(!sonIguales(img1, img2));
  
  liberarLienzo(img1);
  liberarLienzo(img2);
}

void test4(){
  mostrarCartel("Prueba rotarLienzo()");
  Lienzo imgBase, img;
  
  //creo dos lienzos iguales
  reservarLienzo(imgBase, 5, 7);
  rellenarLienzo(imgBase, '.');
  dibujarRectangulo(imgBase, 0, 0, 1, 6, '1');
  dibujarRectangulo(imgBase, 0, 6, 6, 1, '2');
  
  reservarLienzo(img, 5, 7);
  rellenarLienzo(img, '.');
  dibujarRectangulo(img, 0, 0, 1, 6, '1');
  dibujarRectangulo(img, 0, 6, 6, 1, '2');
  
  imprimirLienzo(imgBase);
  
  assert(sonIguales(imgBase, img));
  
  // rotar 3 veces img
  for(int i=0; i<3; ++i){
    rotarLienzo(img);
    imprimirLienzo(img);
    assert(!sonIguales(imgBase, img));
  }
  
  // una rotación más y deberían ser iguales
  rotarLienzo(img);
  imprimirLienzo(img);
  
  assert(sonIguales(imgBase, img));
  
  liberarLienzo(imgBase);
  liberarLienzo(img);
}


void test5(){
  mostrarCartel("Prueba unirLienzos()");
  Lienzo img1, img2, img3;
  
  reservarLienzo(img1, 5, 4);
  rellenarLienzo(img1, '-');
  reservarLienzo(img2, 5, 7);
  rellenarLienzo(img2, '*');
  dibujarRectangulo(img1, 0, 0, 2, 2, '@');
  dibujarRectangulo(img2, 2, 2, 3, 1, '+');
  
  imprimirLienzo(img1);
  imprimirLienzo(img2);
  
  unirLienzos(img3, img1, img2);
  imprimirLienzo(img3);
  
  assert(img3.nc == img1.nc + img2.nc);
  assert(img3.nf == img1.nf);
  
  liberarLienzo(img1);
  liberarLienzo(img2);
  liberarLienzo(img3);
  
}

void test6(){
  mostrarCartel("Prueba copiarRectangulo()");
  
  Lienzo imgBase, img;
  
  reservarLienzo(imgBase, 6, 6);
  rellenarLienzo(imgBase, '@');
  
  dibujarRectangulo(imgBase, 1, 1, 4, 4, 'X');
  imprimirLienzo(imgBase);
  
  copiarRectangulo(img, imgBase, 0, 0, 3, 3);
  assert(img.nf == 3 && img.nc == 3);
  imprimirLienzo(img);
  
  copiarRectangulo(img, imgBase, 1, 1, 4, 4);
  assert(img.nf == 4 && img.nc == 4);
  imprimirLienzo(img);
  
  copiarRectangulo(img, imgBase, 3, 3, 14, 14);
  assert(img.nf == 3 && img.nc == 3);
  imprimirLienzo(img);
  
  liberarLienzo(imgBase);
  liberarLienzo(img);
}


void test7(){
  mostrarCartel("Prueba copiarLienzo()");
  Lienzo img1;
  Lienzo img2;
  Lienzo img3;
  
  reservarLienzo(img1, 5, 5);
  rellenarLienzo(img1, '@');
  copiarLienzo(img2, img1);
  rellenarLienzo(img1, 'X');
  liberarLienzo(img1);
  imprimirLienzo(img2);
  
  reservarLienzo(img3, 3, 3);
  rellenarLienzo(img3, '+');
  copiarLienzo(img1, img3);
  imprimirLienzo(img1);
  
  liberarLienzo(img1);
  liberarLienzo(img2);
  liberarLienzo(img3);
  
}

void test8(){
  mostrarCartel("Prueba todo");
  Lienzo imgBase, img, imgC;
  
  reservarLienzo(imgBase, 5, 5);
  rellenarLienzo(imgBase, '@');
  dibujarRectangulo(imgBase, 0, 0, 5, 5, 'X');
  
  reservarLienzo(img, 5, 5);
  rellenarLienzo(img, '_');
  dibujarRectangulo(img, 2, 0, 1, 5, 'G');
  dibujarRectangulo(img, 1, 4, 3, 1, 'G');
  
  
  imprimirLienzo(imgBase);
  imprimirLienzo(img);
  
  for(int i = 0; i < 4; i++){
    rotarLienzo(img);
    unirLienzos(imgC, imgBase, img);
    copiarLienzo(imgBase, imgC);
    imprimirLienzo(imgBase);
  }
  
  liberarLienzo(imgBase);
  liberarLienzo(img);
  liberarLienzo(imgC);
  
}
