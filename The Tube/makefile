tube: main.o tube.o
	g++ -g main.o tube.o -o tube
main.o: main.cpp tube.h
	g++ -g -c main.cpp
tube.o: tube.cpp tube.h
	g++ -g -c tube.cpp
clean:
	rm -f *.o tube
