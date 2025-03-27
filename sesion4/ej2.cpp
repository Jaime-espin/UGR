#include <iostream>
#include <ctime>
using namespace std;

void menorMayor(const int * const v, const int tam, const int * &ptrmenor, const int * &ptrmayor){
	ptrmenor=ptrmayor=v;
	const int *p;
	for(p=v; p<v+tam; ++p){
		if(*p > *ptrmayor){
			ptrmayor=p;
		}else if (*p < *ptrmenor){
			ptrmenor=p;
		}
	}
}

int main(){
	const int MAX = 100;
	int vector[MAX];
	int usados=20;
	srand(time(NULL));
	for(int i=0; i<usados; i++){ //rellenar array con valores aleatorios
		vector[i]=rand() % MAX + 1;
	}

	const int *ptrMin, *ptrMax;
	menorMayor(vector, usados, ptrMin, ptrMax);
	cout<<"menor: "<<*ptrMin<<", mayor: "<<*ptrMax<<endl;
	
	if (ptrMax <= ptrMin){
		cout<<"Maximo antes del minimo"<<endl;
	}else{
		cout<<"Minimo antes del maximo"<<endl;
	}

	menorMayor(vector, usados/2, ptrMin, ptrMax); // apartado 3:menor mayor primera mitad
	
	//apartado 4: menor mayor segunda mitad
	
	//apartado 5: menor mayor segundo tercio
}
