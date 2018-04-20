words: main.o words.o
	g++ -Wall -g main.o words.o -o words
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: words.h
words.o: words.h
clean: rm -f *.o words
