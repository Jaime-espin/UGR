void ordenarSeleccion(const int v[], const unsigned int longitud, const int *ordenados[]){
        
    inicializarArrayPunteros(v,longitud, ordenados);
        
    const int **inicioArray = ordenados;
    const int **finArray = inicioArray + longitud;
    
    for(const int **contadorI = inicioArray; contadorI < finArray - 1; contadorI++){
        
        const int **min = contadorI;
        
        for(const int **contadorJ = contadorI + 1; contadorJ < finArray; contadorJ++){
            
            if(**contadorJ < **min){
                min = contadorJ;
            }
        }
        if(min != contadorI){
            const int *aux = *contadorI;
            *contadorI = *min;
            *min = aux;
        }
    }
}