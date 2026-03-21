all: bin/multa

bin/multa: obj/main.o obj/tiempo.o obj/registro.o
	g++ -o bin/multa obj/main.o obj/tiempo.o obj/registro.o

obj/main.o: src/main.cpp include/tiempo.h include/registro.h
	g++ -c -I./include -o obj/main.o src/main.cpp

obj/tiempo.o: src/tiempo.cpp include/tiempo.h
	g++ -c -I./include -o obj/tiempo.o src/tiempo.cpp

obj/registro.o: src/registro.cpp include/registro.h include/tiempo.h
	g++ -c -I./include -o obj/registro.o src/registro.cpp

clean:
	rm obj/*.o

cleanall:
	rm obj/*.o bin/*
