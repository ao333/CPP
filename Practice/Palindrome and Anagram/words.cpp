#include <iostream>
#include <cstring>
#include "words.h"
using namespace std;

void reverse(const char* str, char* rev){
  size_t len=strlen(str);
  for(size_t i=0; i<=len; i++)
    rev[i]=str[len-1-i];
  rev[len]='\0';
}

bool compare(const char* one, const char* two){
  char s1[strlen(one)+1];
  char s2[strlen(two)+1];
  format(one,s1);
  format(two,s2);

  if (strlen(s1)==0 && strlen(s2)==0)
    return true;
  if(s1[0]==s2[0])
    return compare(&s1[1], &s2[1]);
  return false;
}

void format(const char* input, char* output){
  int c=0;
  for(size_t i=0; i<=strlen(input); i++){
    if(input[i]=='.' || input[i]==',' || input[i]=='!' || input[i]==' ')
      c++;
    else
      output[i-c]=toupper(input[i]);
  }
}

bool palindrome(const char* sentence){
  char reversed[strlen(sentence)+1];
  reverse(sentence,reversed);
  return (compare(sentence,reversed));
}

bool anagram(const char* str1, const char* str2){
  char s1[strlen(str1)+1];
  char s2[strlen(str1)+1];
  format(str1,s1);
  format(str2,s2);
  selSort(s1);
  selSort(s2);
  return compare(s1,s2);
}

void selSort(char* str){
	char temp;
	int i,j,min,len=strlen(str);

	for(i=0; i<len-1; i++){
		min=i;
		for(j=i+1; j<len; j++){
			if(str[j]<str[min])
				min=j;
		}
		temp=str[i];
		str[i]=str[min];
		str[min]=temp;
	}
}
