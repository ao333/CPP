piglatin: main.o piglatin.o
	g++ -Wall -g main.o piglatin.o -o piglatin
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: piglatin.h
piglatin.o: piglatin.h
clean: rm -f *.o piglatin
