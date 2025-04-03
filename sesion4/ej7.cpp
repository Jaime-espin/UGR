void multiplosDeTres(const int v[], const unsigned int longitud, const int *multTres[]){
    
    unsigned int j=0;
    for(unsigned int i=0; i<longitud; i++){
        
        if(*(v+i) % 3 == 0){
            *(multTres + j) = v + i;
            j++;
        }
    }
    *(multTres + j) = 0;
}