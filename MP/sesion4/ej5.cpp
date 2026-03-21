void organizarArray(int *inicio, const unsigned int tam){
    
    int *izq = inicio;
    int *der = inicio + tam - 1;
    bool continuar = true;
    
    while(continuar){
    
        while(*izq <= *inicio)
            izq++;
        
        while(*der > *inicio)
            der--;
        
        if(izq < der){
            swap(*izq,*der);
        }else{
            continuar = false;
        }
    }
}