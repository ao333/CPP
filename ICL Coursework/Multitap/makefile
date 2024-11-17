multitap: main.o multitap.o
	g++ -Wall -g main.o multitap.o -o multitap
%.o: %.cpp
	g++ -Wall -g -c $<
main.o: multitap.h
multitap.o: multitap.h
