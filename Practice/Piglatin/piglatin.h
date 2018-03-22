#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <fstream>
using namespace std;

int findFirstVowel(const char* word);
void translateWord(const char* english, char* piglatin);
void translateStream(istream& in, ostream& out);

#endif
