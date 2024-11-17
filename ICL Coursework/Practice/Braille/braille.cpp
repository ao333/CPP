#include <iostream>
#include <cctype>
#include <cstring>
#include "braille.h"
using namespace std;

int encode_character(char ch, char* braille){
  // If ch is alpha, move to switch. If ch is alpha and upper, prefix braille, lowercase it and then move to switch
  if (isalpha(ch)){
    if(isupper(ch)){
      strcpy(braille,".....0");
      ch=tolower(ch);
    }
  }
  // If digit, prefix it
  else if(isdigit(ch)){
    strcpy(braille,"..0000");
    if(ch==0)
      // allows '0' to use 'j' as its switch condition
      ch+='j'-'0';
    else
      // allows '1-9' to use 'a-i' as their switch conditions
      ch+='a'-'1';
  }
  // If punctuation, empty the string
  else if(ispunct(ch))
    strcpy(braille,"");
  // Everything else is "......"
  else
    strcpy(braille,"......");

  // code for every alphabet, digit and select punctuations
  switch(ch){
		case 'a': strcat(braille,"0....."); break;
		case 'b': strcat(braille,"00...."); break;
		case 'c': strcat(braille,"0..0.."); break;
		case 'd': strcat(braille,"0..00."); break;
		case 'e': strcat(braille,"0...0."); break;
		case 'f': strcat(braille,"00.0.."); break;
		case 'g': strcat(braille,"00.00."); break;
		case 'h': strcat(braille,"00..0."); break;
		case 'i': strcat(braille,".0.0.."); break;
		case 'j': strcat(braille,".0.00."); break;
		case 'k': strcat(braille,"0.0..."); break;
		case 'l': strcat(braille,"000..."); break;
		case 'm': strcat(braille,"0.00.."); break;
		case 'n': strcat(braille,"0.000."); break;
		case 'o': strcat(braille,"0.0.0."); break;
		case 'p': strcat(braille,"0000.."); break;
		case 'q': strcat(braille,"00000."); break;
		case 'r': strcat(braille,"000.0."); break;
		case 's': strcat(braille,".000.."); break;
		case 't': strcat(braille,".0000."); break;
		case 'u': strcat(braille,"0.0..0"); break;
		case 'v': strcat(braille,"000..0"); break;
		case 'w': strcat(braille,".0.000"); break;
		case 'x': strcat(braille,"0.00.0"); break;
		case 'y': strcat(braille,"0.0000"); break;
		case 'z': strcat(braille,"0.0.00"); break;
    case '.': strcat(braille,".0..00"); break;
    case ',': strcat(braille,".0...."); break;
    case ';': strcat(braille,".00..."); break;
    case '-': strcat(braille,"..0..0"); break;
    case '!': strcat(braille,".00.0."); break;
    case '?': strcat(braille,".00..0"); break;
    case '(': strcat(braille,".00..0"); break;
    case ')': strcat(braille,".00..0"); break;
    case '[': strcat(braille,".00..0"); break;
    case ']': strcat(braille,".00..0"); break;
    case '{': strcat(braille,".00..0"); break;
    case '}': strcat(braille,".00..0"); break;
		default: break;
	}
  return strlen(braille);
}

// iterative
// void encode(const char* text, char* braille){
//   braille[0]='\0';
//   char buf[128];
//   for(size_t i=0; i<strlen(text); i++){
//     buf[0]='\0';
//     encode_character(text[i],buf);
//     strcat(braille,buf);
//   }
// }

void encode(const char* text, char* braille){
  braille[0]='\0';
  encoder(text,braille);
}

void encoder(const char* text, char* braille){
  char buf[128];
  buf[0]='\0';
  encode_character(text[0],buf);
  strcat(braille,buf);

  if(strlen(text)==1)
    return;
  encoder(&text[1],braille);
}

void print_braille(const char* text, ostream& cout){
	char braille[512];
	encode(text,braille);

	for (int row=0; row<3; row++){
		size_t i=row;
  	while(i<strlen(braille)){
  		cout << braille[i];
  		i+=3;
  		cout << braille[i] << " ";
  		i+=3;
  	}
  	cout << endl;
  }

	for(size_t i=0; i<strlen(text); i++){
		if(isupper(text[i]) || isdigit(text[i]))
			cout << "   ";
		cout << text[i] << "  ";
	}

	cout << endl;
}

// void print_braille(const char* text, ostream& cout) {
//   char braille[512];
//   encode(text, braille);
//
//   int col=strlen(braille)/3;
//   for(int r=0; r<3; r++){
//     for(int c=0; c<col; c++){
//       cout << braille[r+c*3];
//       if(c%2)
//         cout << " ";
//     }
//     cout << endl;
//   }
//   for(size_t i=0; i<strlen(text); i++) {
//     if(isdigit(text[i]) || isupper(text[i]))
//       cout << "   ";
//     cout << text[i] << "  ";
//   }
// }
