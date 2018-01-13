#include <iostream>
#include <cstring>
#include <cctype>
#include "soundex.h"
using namespace std;

void encode(const char* surname, char* soundex){
	char code[]={'0','1','2','3','0','1','2','0','0','2','2','4','5','5','0','1','2','6','2','3','0','1','0','2','0','2'};
  size_t n=1;
  soundex[0]=surname[0];

  for(int x=1; x<4; x++){
    while(n<strlen(surname) && (code[surname[n]-'a']=='0' || code[surname[n]-'a']==soundex[x-1]))
      n++;
    if(n<strlen(surname))
      soundex[x]=code[surname[n++]-'a'];
    else
      soundex[x]='0';
  }
  soundex[4]='\0';
}

// int compare(const char* s1, const char* s2){
// 	// assumes only valid soundex code passed in
// 	if (strcmp(s1, "") == 0 && strcmp(s2, "") == 0)
// 		return 1;
//
// 	// recursive case, if same char
// 	if (s1[0] == s2[0])
// 		return compare(&s1[1], &s2[1]);		// pass from [1] onwards
//
// 	// if first char is different
// 	return 0;
// }
bool compare(const char* one, const char* two){
  if(strlen(one)==0 && strlen(two)==0)
    return true;

  if(one[0]==two[0]){
    char onecut[strlen(one)];
    for(size_t i=1; i<=strlen(one); i++)
      onecut[i-1]=one[i];

    char twocut[strlen(two)];
    for(size_t i=1; i<=strlen(two); i++)
      twocut[i-1]=two[i];

    return compare(onecut,twocut);
  }
  return false;
}

int count(const char* surname, const char* sentence){
	char sen_cpy[512],*sen_tok,soundex[5],soundex_tok[5];
	int count=0;

	strcpy(sen_cpy,sentence);
	encode(surname,soundex);

	for(sen_tok=strtok(sen_cpy,", .!"); sen_tok!=NULL; sen_tok=strtok(NULL,", .!")) {
		encode(sen_tok,soundex_tok);
		if(compare(soundex,soundex_tok))
			count++;
	}
	return count;
}

// if(!strcmp(one,two))
//   return true;
// return false;

// void encode(const char* surname, char* soundex){
//   int x=0, n=1;
//   soundex[0]=surname[0];
//
//   for (size_t i=1; i<strlen(soundex); i++)
//     soundex[i]='0';
//
//   while (surname[n]!='\0' && x<4){
//     cout << x << " " << n << " " << soundex[x] << endl;
//     if (surname[n]=='b' || surname[n]=='f' || surname[n]=='p' || surname[n]=='v'){
//       // if (surname[n-1]!='b' || surname[n-1]!='f' || surname[n-1]=='p' || surname[n-1]!='v')
//         soundex[n-x]='1';
//     } else if (surname[n]=='c' || surname[n]=='g' || surname[n]=='j' || surname[n]=='k' || surname[n]=='q' || surname[n]=='s' || surname[n]=='x' || surname[n]=='z'){
//       // if (surname[n-1]!='c' || surname[n-1]!='g' || surname[n-1]!='j' || surname[n-1]!='k' || surname[n-1]!='q' || surname[n-1]!='s' || surname[n-1]!='x' || surname[n-1]!='z')
//         soundex[n-x]='2';
//     } else if (surname[n]=='d' || surname[n]=='t'){
//       // if (surname[n-1]!='d' || surname[n-1]!='t')
//         soundex[n-x]='3';
//     } else if (surname[n]=='l'){
//       // if (surname[n-1]!='l')
//         soundex[n-x]='4';
//     } else if (surname[n]=='m' || surname[n]=='n'){
//       // if (surname[n-1]!='m' || surname[n-1]!='n')
//         soundex[n-x]='5';
//     } else if (surname[n]=='r'){
//       // if (surname[n-1]!='r')
//         soundex[n-x]='6';
//     } else
//         x++;
//       n++;
//   }
//   soundex[4]='\0';
// }

// // func to encode surname into soundex coding system
// void encode(const char* surname, char* soundex){
// 	// First letter
// 	soundex[0] = surname[0];
//
// 	// iterators
// 	int surname_it = 1, soundex_it = 1;
//
// 	while (surname[surname_it] != '\0' && soundex_it < 4)
// 	{
// 		if (letterIn(surname[surname_it], "bfpv")) {
// 			if (soundex[soundex_it -1] != '1') {
// 				soundex[soundex_it] = '1';
// 				soundex_it++;
// 			}
// 		} else if (letterIn(surname[surname_it], "cgjkqsxz")) {
// 			if (soundex[soundex_it -1] != '2') {
// 				soundex[soundex_it] = '2';
// 				soundex_it++;
// 			}
// 		} else if (letterIn(surname[surname_it], "dt")) {
// 			if (soundex[soundex_it -1] != '3') {
// 				soundex[soundex_it] = '3';
// 				soundex_it++;
// 			}
// 		} else if (surname[surname_it] == 'l') {
// 			if (soundex[soundex_it -1] != '4') {
// 				soundex[soundex_it] = '4';
// 				soundex_it++;
// 			}
// 		} else if (letterIn(surname[surname_it], "mn")) {
// 			if (soundex[soundex_it -1] != '5') {
// 				soundex[soundex_it] = '5';
// 				soundex_it++;
// 			}
// 		} else if (surname[surname_it] == 'r') {
// 			if (soundex[soundex_it -1] != '6') {
// 				soundex[soundex_it] = '6';
// 				soundex_it++;
// 			}
// 		}
// 		surname_it++;
// 	}
//
// 	while (soundex_it < 4) {
// 		soundex[soundex_it] = '0';
// 		soundex_it++;
// 	}
// 	soundex[4] = '\0';
// }

// // returns true if char letter within string "phrase"
// bool letterIn(const char letter, const char* phrase) {
// 	int it = 0;
// 	while (phrase[it] != '\0') {
// 		if (letter == phrase[it])
// 			return true;
// 		it++;
// 	}
// 	return false;
// }

// int count(const char* surname, const char* sentence)
// {
// 	int count = 0, sen_tok = 0, buffer_ptr = 0;
// 	char name_buffer[25], soundex[5], buffer_soundex[5];
// 	bool copying = false;
//
// 	// encode original
// 	encode(surname, soundex);
//
// 	while(sentence[sen_tok] != '\0') {
// 		// if name, starts with uppercase letter
// 		if(isupper(sentence[sen_tok]) && !copying) {
// 			// copy name into name_buffer
// 			buffer_ptr = 0;
// 			name_buffer[buffer_ptr] = sentence[sen_tok];
// 			buffer_ptr++;
// 			copying = true;
// 		} else if (copying) {
// 			// continue copying if alpha
// 			if (isalpha(sentence[sen_tok])) {
// 				name_buffer[buffer_ptr] = sentence[sen_tok];
// 				buffer_ptr++;
// 			} else {
// 				// word ending
// 				// stop copying and compare
// 				name_buffer[buffer_ptr] = '\0';
// 				copying = false;
// 				encode(name_buffer, buffer_soundex);
// 				if (compare(soundex, buffer_soundex))
// 					count++;
// 			}
// 		}
// 		sen_tok++;
// 	}
// 	return count;
// }

// int count(const char* surname, const char* sentence) {
//   char temp[20];
//   char temp_encode[5];
//   char sur[20];
//   char surname_encode[5];
//   int num(0), n(0), same(0);
//
//   strcpy(sur,surname);
//   encode(sur, surname_encode);
//   while(num<strlen(sentence)) {
//     if(sentence[num]==','||sentence[num]==' '||sentence[num]=='.'||
//       (num<strlen(sentence)-2&&sentence[num]=='a'&&sentence[num+1]=='n'&&
//       sentence[num+2]=='d')) {
//       temp[index]='\0';
//       encode(temp, temp_encode);
//       if(compare(temp_encode,surname_encode)) same++;
//       index=0;
//     } else {
//       temp[index++]=sentence[num];
//     }
//     num++;
//   }
//
//   return same;
// }
