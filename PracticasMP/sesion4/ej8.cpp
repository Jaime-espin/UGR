void punteroPalabras(const char texto[], const char *ptrIni[]){
    
    unsigned int i=1, n = 0;

    if(*texto != ' '){
        *ptrIni = texto;
        n++;
    }
    
    while(*(texto+i) != '\0'){
        if(*(texto + i) != ' ' && *(texto + i - 1) == ' '){
            *(ptrIni + n) = texto + i;
            n++;
        }
        i++;
    }
    *(ptrIni + n)=texto+i;
}