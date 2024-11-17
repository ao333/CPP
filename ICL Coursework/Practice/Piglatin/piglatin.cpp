#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>
#include "piglatin.h"
using namespace std;

int findFirstVowel(const char* word){
  for(size_t i=0; i<strlen(word); i++){
    char ch=tolower(word[i]);
    if(ch=='a'|| ch=='e'|| ch=='i'|| ch=='o'|| ch=='u' || ch=='y'){
      if(ch=='y' && (i==0 || i==strlen(word)-1))
        continue;
      else
        return i;
    }
  }
  return -1;
}

void translateWord(const char* english, char* piglatin){
  int pos=findFirstVowel(english);
  char one[100],two[100],eng[100];
  char punct;
  strcpy(eng,english);

  // If first char is a punctuation, cut it
  if(ispunct(eng[strlen(eng)-1])){
    punct=eng[strlen(eng)-1];
    eng[strlen(eng)-1]='\0';
  }
  // If first char is digit, return english
  if(isdigit(eng[0])){
    strcpy(piglatin,eng);
    return;
  }
  // If first char is vowel, append "way"
  if(pos==0){
    strcpy(piglatin,eng);
    strcat(piglatin,"way");
  }
  // Else, bring the string part after pos to the front, append the part before pos, and then append ay if vowel exists
  else if(pos>0){
    for(int i=0; i<pos; i++){
      one[i]=eng[i];
      one[pos]='\0';
    }
    for(size_t i=pos; i<=strlen(eng); i++){
      two[i-pos]=eng[i];
    }
    strcpy(piglatin,two);
    strcat(piglatin,one);
    strcat(piglatin,"ay");
  }
  // If first char of english is a capital, capitalize the first piglatin char, and then lowercase every subsequent one
  if(isupper(eng[0]))
    for(size_t i=1; i<strlen(piglatin); i++){
      piglatin[0]=toupper(piglatin[0]);
      piglatin[i]=tolower(piglatin[i]);
  }
  // If punct is assigned a value, append it to the end of piglatin
  if(punct)
    piglatin[strlen(piglatin)]=punct;
}

void translateStream(istream& in, ostream& out){
  char eng[65],pig[65];
  char ch;
  // If the stream hasn't ended (in.get isn't reading an end-of-file character), copy the character into ch
  if(in.get(ch)){
    // If the character is alphanumeric (the only characters translateWord can deal with)
    if(isalnum(ch)){
      // Move he pointer back and put ch back
      in.putback(ch);
      // read that character into english
      in >> eng;
      translateWord(eng,pig);
      // Output the translated piglatin into the output stream
      out << pig;
      // If not alphanumeric, just output the character
    } else
        out << ch;

    translateStream(in,out);
  }
}

// // iterative
// void translateStream(istream& in, ostream& out){
//   char eng[65],pig[65];
//   char ch;
//     while(in.get(ch)){
//       if(isalnum(ch)){
//         in.putback(ch);
//         in >> eng;
//         translateWord(eng,pig);
//         out << pig;
//       }
//       else
//         out << ch;
//     }
// }
