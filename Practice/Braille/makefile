braille: main.o braille.o
	g++ -Wall -g main.o braille.o -o braille
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: braille.h
braille.o: braille.h
clean: rm -f *.o braille
