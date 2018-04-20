#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <string>
#include "multitap.h"
using namespace std;

int encode_character(char ch, char multitap[]){
  multitap[0] = '\0';

  if(isupper(ch))
    strcat(multitap,"#");

  if(isdigit(ch)){
    strcpy(multitap,"*");
    multitap[1]=ch;
    multitap[2]='\0';
  }

  char low_ch=tolower(ch);

  switch(low_ch){
    case'a':strcat(multitap,"2");break;
    case'b':strcat(multitap,"22");break;
    case'c':strcat(multitap,"222");break;
    case'd':strcat(multitap,"3");break;
    case'e':strcat(multitap,"33");break;
    case'f':strcat(multitap,"333");break;
    case'g':strcat(multitap,"4");break;
    case'h':strcat(multitap,"44");break;
    case'i':strcat(multitap,"444");break;
    case'j':strcat(multitap,"5");break;
    case'k':strcat(multitap,"55");break;
    case'l':strcat(multitap,"555");break;
    case'm':strcat(multitap,"6");break;
    case'n':strcat(multitap,"66");break;
    case'o':strcat(multitap,"666");break;
    case'p':strcat(multitap,"7");break;
    case'q':strcat(multitap,"77");break;
    case'r':strcat(multitap,"777");break;
    case's':strcat(multitap,"7777");break;
    case't':strcat(multitap,"8");break;
    case'u':strcat(multitap,"88");break;
    case'v':strcat(multitap,"888");break;
    case'w':strcat(multitap,"9");break;
    case'x':strcat(multitap,"99");break;
    case'y':strcat(multitap,"999");break;
    case'z':strcat(multitap,"9999");break;
    case' ':strcat(multitap,"0");break;
    case'.':strcat(multitap,"1");break;
    case',':strcat(multitap,"11");break;
    case'!':strcat(multitap,"111");break;
    case'?':strcat(multitap,"1111");break;
  }
  return strlen(multitap);
}

void encode(const char plaintext[], char multitap[]){
  char output[512];
  int len;

  multitap[0]='\0';

  for(int i=0; i<strlen(plaintext); i++){
    encode_character(plaintext[i],output);

    if(isupper(plaintext[i-1]) && islower(plaintext[i]))
      strcat(multitap,"#");

    len=strlen(multitap);
    if(output[0]==multitap[len-1])
      strcat(multitap,"|");

    strcat(multitap,output);
  }
}

char decode_character(const char multitap[]) {
  char output[512];

  for(int i='a'; i<='z'; i++){
    encode_character((char)i,output);
    if(!strcmp(output,multitap))
      return (char) i;
  }

  if(!strcmp(multitap,"0"))
    return ' ';
  if(!strcmp(multitap,"1"))
    return '.';
  if(!strcmp(multitap,"11"))
    return ',';
  if(!strcmp(multitap,"111"))
    return '!';
  if(!strcmp(multitap,"1111"))
    return '?';

  return '@';
}

void print_decode(const char* input, ostream& out, bool caps) {
	char ch = decode_character(input);

	if (isalpha(ch) && caps)
		ch = toupper(ch);
	out << ch;
}

void decode(istream& in, ostream& out) {
	char ch, word_buf[512];
	bool caps = false;
	int len;
	word_buf[0] = '\0';

	while (in.get(ch)) {
		if(ch == '#') {
			if(word_buf[0]) print_decode(word_buf,out,caps);

      word_buf[0] = '\0';

			caps? caps = false : caps = true;
			continue;
		}

		if(ch == '|') {
			print_decode(word_buf,out,caps);
			word_buf[0] = '\0';
			continue;
		}

		if(ch == '*') {
			print_decode(word_buf, out, caps);
			in.get(ch);
			out<<ch;
			word_buf[0] = '\0';
			continue;
		}

		if(isdigit(ch)) {
			len = strlen(word_buf);

			if (len == 0) {
				word_buf[0] = ch;
				word_buf[1] = '\0';
			} else if (ch == word_buf[len -1]) {
				word_buf[len] = ch;
				word_buf[len + 1] = '\0';
			} else {
				print_decode(word_buf, out, caps);
				word_buf[0] = ch;
				word_buf[1] = '\0';
			}
		}
	}

	print_decode(word_buf, out, caps);
	cout << endl;
}
