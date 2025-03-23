# NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
# DNI: 75571535K
# GRUPO DE PRÁCTICAS: Jueves

all: bin/automata

bin/automata: obj/ace.o obj/automata.o
	g++ -o bin/automata obj/ace.o obj/automata.o

obj/ace.o: src/ace.cpp
	g++ -c -I./include -o obj/ace.o src/ace.cpp

obj/automata.o: src/automata.cpp
	g++ -c -I./include -o obj/automata.o src/automata.cpp

clean:
	rm obj/*

cleanall:
	rm obj/* bin/*