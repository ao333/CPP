#include <iostream>
#include <cstring>
#include <cctype>
#include "shrink.h"
using namespace std;

int lookup(const char* word, const char* dictionary[]){
  int i = 0;
  char word_buf[100];

  do {
    strcpy(word_buf, dictionary[i]);
    if (!strcmp(word,word_buf)) return i;
    i++;
  } while (strcmp(word_buf,""));
  return -1;
}

void encode(const char* word, char compressed[100], const char* dictionary[]){
  int pos;

  if (strlen(word) == 2){
    if (isalnum(word[0]) && isalnum(word[1])){
      compressed[0] = '!';
      compressed[1] = word[0];
      compressed[2] = word[1];
      compressed[3] = '\0';
      return;
    }
  }

  pos = lookup(word,dictionary);
  if (pos > -1){
    if (pos < 10){
      compressed[0] = '0';
      compressed[1] = (char)(((int)'0')+pos);
    }
    else if (pos < 100){
      compressed[0] = (char)(((int)'0')+pos/10);
      compressed[1] = (char)(((int)'0')+pos%10);
    }
    else{
      cerr << "pos out of 00 - 99 range with value: " << pos << endl;
    }
    compressed[2] = '\0';
    return;
  }
  strcpy(compressed,word);
  return;
}
