sonnet:main.o sonnet.o
	g++ -Wall -g main.o sonnet.o -o sonnet
%.o: %.c
	g++ -Wall -g -c $<
main.o:sonnet.h
sonnet.o:sonnet.h
