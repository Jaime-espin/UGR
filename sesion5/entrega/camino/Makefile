all: bin/camino

bin/camino: obj/main.o obj/camino.o obj/test.o
	g++ -o bin/test obj/main.o obj/camino.o obj/test.o

obj/main.o: src/main.cpp include/camino.h include/test.h
	g++ -Iinclude -c -o obj/main.o src/main.cpp

obj/camino.o: src/camino.cpp include/camino.h
	g++ -Iinclude -c -o obj/camino.o src/camino.cpp

obj/test.o: src/test.cpp include/camino.h include/test.h
	g++ -Iinclude -c -o obj/test.o src/test.cpp

clean:
	rm -f obj/*.o

cleanall:
	rm -f obj/*.o bin/*