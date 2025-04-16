/*
NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
DNI: 75571535K
GRUPO DE PR´ACTICAS: Jueves
*/
#include <iostream>
#include "lienzo.h"
using namespace std;

void reservarLienzo(Lienzo &l, int nf, int nc){
    l.nf=nf;
    l.nc=nc;
    l.m = new char*[l.nf];
    for (int i = 0; i < l.nf; ++i){
        l.m[i] = new char[l.nc];
    }
}

void liberarLienzo(Lienzo &l){
    if(l.m != nullptr){
        for (int i = 0; i < l.nf; ++i) {
            delete[] l.m[i];
        }
        delete[] l.m;
        l.m = nullptr;
    }
}

void rellenarLienzo(Lienzo &l, char c){
    for (int i = 0; i < l.nf; ++i) {
        for (int j = 0; j < l.nc; ++j) {
            l.m[i][j] = c;
        }
    }
}

void imprimirLienzo(Lienzo l){
    for (int i = 0; i < l.nf; ++i) {
        for (int j = 0; j < l.nc; ++j) {
            cout<<l.m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void dibujarRectangulo(Lienzo & l, int fil, int col, int ancho, int alto, char c){
    int filInicio, colInicio, filFin, colFin;
    if(fil<0){
        filInicio=0;
    }else{
        filInicio=fil;
    }
    if(col<0){
        colInicio=0;
    }else{
        colInicio=col;
    }
    if(fil+alto > l.nf -1){
        filFin=l.nf-1;
    }else{
        filFin=filInicio+alto-1;
    }
    if(col+ancho > l.nc -1){
        colFin=l.nc-1;
    }else{
        colFin=colInicio+ancho-1;
    }

    for (int i = filInicio; i <= filFin; i++) {
        for (int j = colInicio; j <= colFin; j++) {
            l.m[i][j] = c;
        }
    }
}
void rotarLienzo(Lienzo & l){
    Lienzo laux;
    copiarLienzo(laux, l);
    liberarLienzo(l);
    reservarLienzo(l, laux.nc, laux.nf);
    for(int i=0; i<l.nf; i++){
        for(int j=0; j<l.nc; j++){
            l.m[i][j]=laux.m[laux.nf - 1 - j][i];
        }
    }
    liberarLienzo(laux);
}
void unirLienzos(Lienzo & l, Lienzo l1, Lienzo l2){
    liberarLienzo(l);
    int totalCol=l1.nc+l2.nc;
    int totalFil;
    if(l1.nf==l2.nf){
        totalFil=l1.nf;
    }
    reservarLienzo(l, totalFil, totalCol);
    for(int i=0; i<l1.nf; i++){
        for(int j=0; j<l1.nc; j++){
            l.m[i][j]=l1.m[i][j];
        }
    }
    for(int i=0; i<l2.nf; i++){
        for(int j=l1.nc; j<totalCol; j++){
            l.m[i][j]=l2.m[i][j-l1.nc];
        }
    }
}
void copiarRectangulo(Lienzo & l, Lienzo l1, int fil, int col, int alto, int ancho){
    int filFin=fil+alto-1;
    if(filFin>l1.nf){
        filFin=l1.nf-1;
        alto=filFin - fil + 1;
    }
    int colFin=col+ancho-1;
    if(colFin>l1.nc){
        colFin=l1.nc-1;
        ancho = colFin - col + 1;
    }
    reservarLienzo(l, alto, ancho);
    for(int i=fil; i<=filFin; i++){
        for(int j=col; j<=colFin;j++){
            l.m[i-fil][j-col]=l1.m[i][j];
        }
    }
}
bool sonIguales(Lienzo l1, Lienzo l2){
    if(l1.nf != l2.nf || l1.nc != l2.nc){
        return false;
    }else{
        for(int i=0; i<l1.nf; i++){
            for(int j=0; j<l1.nc; j++){
                if(l1.m[i][j] != l2.m[i][j]){
                    return false;
                }
            }
        }
    }
    return true;
}
void copiarLienzo(Lienzo & lcopia, Lienzo l){
    liberarLienzo(lcopia);
    reservarLienzo(lcopia, l.nf, l.nc);
    for(int i=0; i<l.nf; i++){
        for(int j=0; j<l.nc; j++){
            lcopia.m[i][j]=l.m[i][j];
        }
    }
}