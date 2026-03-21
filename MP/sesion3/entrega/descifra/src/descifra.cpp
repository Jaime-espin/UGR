/*
NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
DNI: 75571535K
GRUPO DE PRÁCTICAS: Jueves
*/

#include <string>
#include "descifra.h"
using namespace std;

unsigned int longitudCad(const char cs[]){
	unsigned int i=0;
	while(cs[i] != '\0'){
		i++;
	}
	return i;
}

bool cojoLetra(const char cs[], int j){
	return j==0 || cs[j-1]==' ' || cs[j+1]==' ';
}

void descifra(const char cs[], char rta[]){
	int j=0;
	for(int i=0; i<longitudCad(cs); i++){
		if(cojoLetra(cs, i)){
			rta[j++]=cs[i];
		}
	}
	rta[j]='\0';
}
