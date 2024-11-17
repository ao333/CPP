statistics: main.o statistics.o
	g++ -g main.o statistics.o -o statistics
main.o: main.cpp statistics.h
	g++ -g -c main.cpp
statistics.o: statistics.cpp statistics.h
	g++ -g -c statistics.cpp
clean:
	rm -f *.o statistics
