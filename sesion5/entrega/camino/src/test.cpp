#include <iostream>
#include "camino.h"

using namespace std;

int main(){
    Camino c;
    /*mostrarCamino(c);

    Punto2D p;

    cin>>p.x>>p.y;

    agregarPunto(c, p);

    mostrarCamino(c);

    Punto2D pborra;

    cin>>pborra.x>>pborra.y;

    borrarPunto(c, p);

    mostrarCamino(c);*/

    Punto2D p1;
    p1.x=0;
    p1.y=0;

    Punto2D p2;
    p2.x=3;
    p2.y=3;

    Punto2D p3;
    p3.x=1;
    p3.y=1;
    agregarPunto(c, p1);
    agregarPunto(c, p2);
    agregarPunto(c, p3);

    mostrarCamino(c);

    /*Punto2D plejano1, plejano2;

    masLejanos(c, plejano1, plejano2);
    cout<< plejano1.x <<","<< plejano1.y<<endl;
    cout<< plejano2.x <<","<< plejano2.y<<endl;

    cout<<longitud(c)<<endl;*/

    Camino c2;
    Punto2D p4;
    p4.x=5;
    p4.y=5;

    Punto2D p5;
    p5.x=2;
    p5.y=2;

    Punto2D p6;
    p6.x=8;
    p6.y=8;
    agregarPunto(c2, p4);
    agregarPunto(c2, p5);
    agregarPunto(c2, p6);

    mostrarCamino(c2);

    Camino cUnion;
    unirCaminos(c,c2,cUnion);

    mostrarCamino(cUnion);
}