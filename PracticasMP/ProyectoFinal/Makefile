CPPFLAGS = -g -std=c++11
LDFLAGS = -L./lib -lraylib -lm -lpthread -ldl -lrt #-lX11 -lGL

all : bin/test0 bin/test1 bin/test2 bin/test_raylib

bin/test_raylib : obj/main_raylib.o obj/ConjuntoParticulas.o obj/Particula.o obj/Vector2D.o obj/util.o
	g++ $(CPPFLAGS) -o bin/test_raylib obj/main_raylib.o obj/ConjuntoParticulas.o obj/Particula.o obj/Vector2D.o obj/util.o $(LDFLAGS)

obj/main_raylib.o : src/main_raylib.cpp include/Particula.hpp include/util.hpp include/Vector2D.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/main_raylib.o src/main_raylib.cpp

bin/test0 : obj/test0.o obj/Particula.o obj/Vector2D.o obj/util.o
	g++ $(CPPFLAGS) -o bin/test0 obj/test0.o obj/Particula.o obj/Vector2D.o obj/util.o

bin/test1 : obj/test1.o obj/Particula.o obj/Vector2D.o obj/util.o obj/ConjuntoParticulas.o
	g++ $(CPPFLAGS) -o bin/test1 obj/test1.o obj/Particula.o obj/Vector2D.o obj/util.o obj/ConjuntoParticulas.o

bin/test2 : obj/test2.o obj/Particula.o obj/Vector2D.o obj/util.o obj/ConjuntoParticulas.o
	g++ $(CPPFLAGS) -o bin/test2 obj/test2.o obj/Particula.o obj/Vector2D.o obj/util.o obj/ConjuntoParticulas.o

obj/test0.o : src/main_test.cpp include/Particula.hpp include/util.hpp include/Vector2D.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/test0.o src/main_test.cpp

obj/test1.o : src/main_test1.cpp include/Particula.hpp include/util.hpp include/Vector2D.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/test1.o src/main_test1.cpp

obj/test2.o : src/main_test2.cpp include/Particula.hpp include/util.hpp include/Vector2D.hpp include/ConjuntoParticulas.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/test2.o src/main_test2.cpp

obj/Particula.o : src/Particula.cpp include/util.hpp include/Vector2D.hpp include/Particula.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/Particula.o src/Particula.cpp

obj/ConjuntoParticulas.o : src/ConjuntoParticulas.cpp include/util.hpp include/Vector2D.hpp include/ConjuntoParticulas.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/ConjuntoParticulas.o src/ConjuntoParticulas.cpp

obj/Vector2D.o : src/Vector2D.cpp include/util.hpp include/Vector2D.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/Vector2D.o src/Vector2D.cpp

obj/util.o : src/util.cpp include/util.hpp
	g++ $(CPPFLAGS) -c -I./include -o obj/util.o src/util.cpp

clean:
	@echo "Limpiando archivos..."
	rm bin/* obj/*.o