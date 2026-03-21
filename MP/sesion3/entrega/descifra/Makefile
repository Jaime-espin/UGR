
#NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
#DNI: 75571535K
#GRUPO DE PRÁCTICAS: Jueves
all: bin/descifra
bin/descifra: obj/pruebaDescifra.o obj/descifra.o
	g++ -o bin/descifra obj/pruebaDescifra.o obj/descifra.o
obj/pruebaDescifra.o: src/pruebaDescifra.cpp include/descifra.h
	g++ -c -I./include -o obj/pruebaDescifra.o src/pruebaDescifra.cpp
obj/descifra.o: src/descifra.cpp include/descifra.h
	g++ -c -I./include -o obj/descifra.o src/descifra.cpp
clean:
	rm obj/*.o
cleanall:
	rm obj/*.o bin/*
