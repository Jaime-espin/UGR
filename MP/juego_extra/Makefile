all: bin/juego

bin/juego: obj/main_juego.o obj/Vector2D.o obj/Particula.o obj/util.o obj/escudo.o
	g++ -o bin/juego obj/main_juego.o obj/Vector2D.o obj/Particula.o obj/util.o obj/escudo.o ./lib/libraylib.a -lm -lpthread -ldl -lrt

obj/main_juego.o: src/main_juego.cpp
	g++ -c -I./include -o obj/main_juego.o src/main_juego.cpp

obj/Vector2D.o: src/Vector2D.cpp
	g++ -c -I./include -o obj/Vector2D.o src/Vector2D.cpp

obj/Particula.o: src/Particula.cpp
	g++ -c -I./include -o obj/Particula.o src/Particula.cpp

obj/util.o: src/util.cpp
	g++ -c -I./include -o obj/util.o src/util.cpp

obj/escudo.o: src/escudo.cpp
	g++ -c -I./include -o obj/escudo.o src/escudo.cpp

clean:
	rm obj/*.o

cleanall: clean
	rm obj/*.o bin/*