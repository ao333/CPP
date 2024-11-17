playfair: main.o playfair.o
	g++ -Wall -g main.o playfair.o -o playfair
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: playfair.h
playfair.o: playfair.h
clean: rm -f *.o playfair
