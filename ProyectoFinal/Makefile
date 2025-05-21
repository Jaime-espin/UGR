all: bin/proyecto_final
prep: bin/test_preparacion
test1: bin/test1

bin/test1:obj/main_test1.o obj/vector.o obj/particula.o obj/util.o obj/ConjuntoParticulas.o
	g++ -o bin/test1 obj/main_test1.o obj/vector.o obj/particula.o obj/util.o obj/ConjuntoParticulas.o

bin/proyecto_final: obj/main.o obj/vector.o obj/particula.o obj/util.o obj/ConjuntoParticulas.o
	g++ -o bin/proyecto obj/main.o obj/vector.o obj/particula.o obj/util.o obj/ConjuntoParticulas.o ./lib/libraylib.a -lm -lpthread -ldl -lrt

bin/test_preparacion: obj/main_test.o obj/vector.o obj/particula.o obj/util.o obj/ConjuntoParticulas.o
	g++ -o bin/proyecto_test obj/main_test.o obj/vector.o obj/particula.o obj/util.o obj/ConjuntoParticulas.o

obj/main_test.o: src/main_test.cpp
	g++ -c -I./include -o obj/main_test.o src/main_test.cpp

obj/main_test1.o: src/main_test1.cpp
	g++ -c -I./include -o obj/main_test1.o src/main_test1.cpp

obj/main.o: src/main.cpp
	g++ -c -I./include -o obj/main.o src/main.cpp

obj/vector.o: src/vector.cpp
	g++ -c -I./include -o obj/vector.o src/vector.cpp

obj/particula.o: src/particula.cpp
	g++ -c -I./include -o obj/particula.o src/particula.cpp

obj/util.o: src/util.cpp
	g++ -c -I./include -o obj/util.o src/util.cpp

obj/ConjuntoParticulas.o: src/ConjuntoParticulas.cpp
	g++ -c -I./include -o obj/ConjuntoParticulas.o src/ConjuntoParticulas.cpp

clean:
	rm obj/*.o

cleanall: clean
	rm obj/*.o bin/*