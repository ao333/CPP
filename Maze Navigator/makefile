maze: main.o maze.o
	g++ -g -Wall main.o maze.o -o maze
%.o: %.c
	g++ -g -Wall $<
main.o: maze.h
maze.o: maze.h
clean: rm -f *.o maze
