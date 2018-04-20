substring: main.o substring.o
	g++ -Wall -g main.o substring.o -o substring
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: substring.h
substring.o: substring.h
clean: rm -f *.o substring
