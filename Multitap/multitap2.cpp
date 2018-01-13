#include "multitap.h"
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

int encode_character(char ch, char* multitap){
	int num, count;
	if(isdigit(ch)){
		multitap[0] = '*';
		multitap[1] = ch;
		multitap[2] = '\0';
		return 2;
	}
	else{
		encode_ch_help(ch, num, count);
		for(int i = 0; i < count; i++){
			multitap[i] = '0' + num;
		}
		multitap[count] = '\0';
		return count;
	}
}

void encode_ch_help(char ch, int& num, int& count){
	ch = tolower(ch);
	if(ch == ' '){
		count = 1;
		num = 0;
		return;
	}
	if(!isalpha(ch)){
		num = 1;
		if(ch == '.') count = 1;
		if(ch == ',') count = 2;
		if(ch == '!') count = 3;
		if(ch == '?') count = 4;
	}
	else{
		int alphanum;
		if(ch == 's'){
			count = 4;
			num = 7;
			return;
		}
		if(ch == 'z'){
			count = 4;
			num = 9;
			return;
		}
		if(ch >= 'a' && ch < 's'){
			alphanum  = ch - 'a';
			count = alphanum % 3 + 1;
			num = alphanum / 3 + 2;
		}
		if(ch > 's' && ch < 'z'){
			alphanum = ch - 't';
			count = alphanum % 3 + 1;
			num = alphanum / 3 + 8;
		}
	}
}

void encode_help(const char* plaintext, char* multitap){
	if(!plaintext[0]) return;
	char lastch = ' ';
	int length = strlen(multitap);
	if(length > 0) lastch = multitap[length - 1];
	char multitap_ch[8];
	encode_character(plaintext[0], multitap_ch);
	if(lastch == multitap_ch[0] && !isupper(plaintext[0])){
		strcat(multitap, "|");
	}
	if(isupper(plaintext[0])){
		strcat(multitap, "#");
	}
	strncat(multitap, multitap_ch, 8);
	encode_help(&plaintext[1], multitap);
}

void encode(const char* plaintext, char* multitap){
	multitap[0] = '\0';
	encode_help(plaintext, multitap);
}

char decode_character(const char* multitap){
	char mc[8];
	for(char c = 'a'; c <= 'z'; c++){
		encode_character(c, mc);
		if(strcmp(mc, multitap) == 0) return c;
	}
	for(char c = '0'; c <= '9'; c++){
		encode_character(c, mc);
		if(strcmp(mc, multitap) == 0) return c;
	}
	char noalnum[5] = {' ', '.', ',', '!', '?'};
	for(int i = 0; i < 5; i++){
		encode_character(noalnum[i], mc);
		if(strcmp(mc, multitap) == 0) return noalnum[i];
	}
	return '\n';
}

void decode(istream& input, ostream& output){
	char multitap[512];
	char multitap_ch[8];
	char outputchar;
	while(input.getline(multitap, 512)){
		int i = 0, count = 0;
		bool upperflag = false;
		while(multitap[i]){
			if(i > 0 && multitap[i] != multitap[i - 1] && multitap[i - 1] != '|'
					&& multitap[i - 1] != '#' && multitap[i - 1] != '*'){
				multitap_ch[count] = '\0';
				if(upperflag){
					outputchar = toupper(decode_character(multitap_ch));
					upperflag = false;
				}
				else outputchar = decode_character(multitap_ch);
				output << outputchar;
				count = 0;
			}
			if(multitap[i] == '|'){
				i++;
				continue;
			}
			if(multitap[i] == '#'){
				i++;
				upperflag = true;
				continue;
			}
			multitap_ch[count] = multitap[i];
			count++;
			i++;
		}
		output << endl;
	}

}
