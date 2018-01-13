#ifndef MAZE_H
#define MAZE_H

#include <fstream>
using namespace std;

int encode_character(char ch, char* braille);
void encode(const char* text, char* braille);
void encoder(const char* text, char* braille);
void print_braille(const char* text, ostream& cout);

#endif
