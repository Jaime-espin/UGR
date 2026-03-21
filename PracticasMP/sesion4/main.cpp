inicializarArrayPunteros(const int v[], const unsigned int longitud, const int *arrayPtr[]){
        
    for(int i = 0; i< longitud; i++){
        *(arrayPtr+i) =v+i;
    }
}