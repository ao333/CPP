#include "playfair.h"
#include <cctype>
#include <iostream>
#include <cstring>
using namespace std;

void prepare(const char input[], char output[]){
	int count=0;
	output[0]='\0';

	for(int i=0;i<strlen(input);i++){
		if(ispunct(input[i])||isspace(input[i])){
			count++;
			continue;
		}
		else
			output[i-count]=toupper(input[i]);
	}
	output[strlen(output)]='\0';

	if(strlen(output)%2==1)
		strcat(output,"X");
}

bool occurs_before(const char str[], char letter,int pos){
	for(int i=0;i<pos;i++)
		if(str[i]==letter) return true;
	return false;
}

void grid(const char codeword[], char square[6][6]){
	int i,len=strlen(codeword);
	char buf[512];
	buf[0]='\0';
	int count=0;

	for(int j=0;j<len;j++)
		if(!occurs_before(codeword,codeword[j],j)){
			buf[count]=codeword[j];
			count++;
		}

	for(i=0;i<strlen(buf);i++){
		square[i/6][i%6]=buf[i];
	}

	for(char c='A';c<='Z';c++){
		if(!occurs_before(codeword,c,len)){
			square[i/6][i%6]=c;
			i++;
		}
	}

	for(char n='0';n<='9';n++){
		if(!occurs_before(codeword,n,len)){
			square[i/6][i%6]=n;
			i++;
		}
	}
}

void bigram(char square[6][6], char inchar1, char inchar2, char& outchar1, char& outchar2){
	int r1,r2,c1,c2;

	for(int r=0;r<6;r++)
		for(int c=0;c<6;c++)
			if(square[r][c]==inchar1){
				r1=r;
				c1=c;
				break;
			}

	for(int r=0;r<6;r++)
		for(int c=0;c<6;c++)
			if(square[r][c]==inchar2){
				r2=r;
				c2=c;
				break;
			}

	outchar1=square[r1][c2];
	outchar2=square[r2][c1];
}

void encode(char square[6][6], char prepared[], char encoded[]){

	for(int i=0;i<strlen(prepared);i+=2)
		bigram(square,prepared[i],prepared[i+1],encoded[i],encoded[i+1]);
}

// recursive
// void encode(char square[6][6], char prepared[], char encoded[]){
// 	if(!prepared[0]||!prepared[1]){
// 		encoded[0]='\0';
// 		return;
// 	}
// 	bigram(square,prepared[0],prepared[1],encoded[0],encoded[1]);
// 	encode(square, &prepared[2], &encoded[2]);
// }

void decode(char square[6][6], char encoded[], char decoded[]){
	encode(square,encoded,decoded);
}
