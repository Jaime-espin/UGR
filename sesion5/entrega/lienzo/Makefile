all: bin/lienzo

bin/lienzo: obj/main.o obj/lienzo.o obj/test.o
	g++ -o bin/lienzo obj/main.o obj/lienzo.o obj/test.o

obj/main.o: src/main.cpp include/lienzo.h include/test.hpp
	g++ -Iinclude -c -o obj/main.o src/main.cpp

obj/lienzo.o: src/lienzo.cpp include/lienzo.h
	g++ -Iinclude -c -o obj/lienzo.o src/lienzo.cpp

obj/test.o: src/test.cpp include/lienzo.h include/test.hpp
	g++ -Iinclude -c -o obj/test.o src/test.cpp

clean:
	rm -f obj/*.o

cleanall:
	rm -f obj/*.o bin/*