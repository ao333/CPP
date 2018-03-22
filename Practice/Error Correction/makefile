correct: main.o correct.o
	g++ -Wall -g main.o correct.o -o correct
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: correct.h
correct.o: correct.h
clean: rm -f *.o correct
