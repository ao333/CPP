#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include "sonnet.h"
using namespace std;

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }

  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

int count_words(const char* line){
  int count=1;
  char output[512];

  while(get_word(line,count,output))
    count++;

  return count-1;
}

bool find_phonetic_ending(const char* word,char* ending){
  ifstream in("dictionary.txt");
  char line[512],firstWord[512],endWord[512];
  ending[0]='\0';

  while(in.getline(line,512)){
    get_word(line,1,firstWord);

    if(!strcmp(word,firstWord)){
      int index=count_words(line);

      while(index>1){
        get_word(line,index,endWord);

        if(isVowel(endWord[0])){
          strcat(endWord,ending);
          strcpy(ending,endWord);

          in.close();
          return true;
        }
        strcat(endWord,ending);
        strcpy(ending,endWord);
        index--;
      }
      in.close();
      return false;
    }
  }
  in.close();
  return false;
}

bool isVowel(char ch){
  ch=tolower(ch);
  switch(ch){
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return true;
		default: return false;
	}
}

bool find_rhyme_scheme(const char* filename, char* scheme){
  ifstream in(filename);
  char line[512],endWord[512],ending[512];
  int i=0;

  rhyming_letter(RESET);

  while(in.getline(line,512)){
    get_word(line,count_words(line),endWord);
    find_phonetic_ending(endWord,ending);
    scheme[i]=rhyming_letter(ending);
    i++;
  }
	scheme[i]='\0';
	return true;
}

const char* identify_sonnet(const char* filename){
  ifstream in(filename);
  char scheme[512];

  find_rhyme_scheme(filename,scheme);
  if(!strcmp(scheme,"ababcdcdefefgg"))
    return "Shakespearean";
  else if(!strcmp(scheme,"abbaabbacdcdcd"))
    return "Petrarchan";
  else if (!strcmp(scheme,"ababbcbccdcdee"))
    return "Spenserian";
  else
    return "Unknown";
}
