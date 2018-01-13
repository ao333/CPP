river: main.o river.o
	g++ -Wall -g main.o river.o -o river
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: river.h
river.o: river.h
