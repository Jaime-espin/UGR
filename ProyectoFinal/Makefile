all: bin/proyecto

bin/proyecto: obj/main.o obj/vector.o obj/particula.o obj/util.o
	g++ -o bin/proyecto obj/main.o obj/vector.o obj/particula.o obj/util.o

obj/main.o: src/main_test.cpp
	g++ -c -I./include -o obj/main.o src/main_test.cpp

obj/vector.o: src/vector.cpp
	g++ -c -I./include -o obj/vector.o src/vector.cpp

obj/particula.o: src/particula.cpp
	g++ -c -I./include -o obj/particula.o src/particula.cpp

obj/util.o: src/util.cpp
	g++ -c -I./include -o obj/util.o src/util.cpp

clean:
	rm obj/*.o

cleanall: clean
	rm obj/*.o bin/*