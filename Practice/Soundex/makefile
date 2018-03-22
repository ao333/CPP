soundex: main.o soundex.o
	g++ -Wall -g main.o soundex.o -o soundex
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: soundex.h
soundex.o: soundex.h
clean: rm -f *.o soundex
