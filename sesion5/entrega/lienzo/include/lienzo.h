struct Lienzo {
	char ** m = 0;
	int nf = 0, nc = 0;
};

void reservarLienzo(Lienzo l,);
void liberarLienzo(Lienzo l);
void rellenarLienzo(Lienzo & l, char caracter);
void dibujarRectangulo(Lienzo & l, int fil, int col, int ancho, int alto);
void rotarLienzo(Lienzo & l);
Lienzo unirLienzos(Lienzo l1, Lienzo l2);
