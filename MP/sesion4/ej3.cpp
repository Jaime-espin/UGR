void invierteCadena(char * cad){
	char *fin=cad;
	while(*fin != '\0'){ //while(*fin++)
		fin++;
	}
	fin--;
	char *inicio = cad;
	while(inicio<fin){
		swap(*inicio++,*fin--);
	}
}
