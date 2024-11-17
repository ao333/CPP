#include <iostream>
#include <cstring>
using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch,char*binary){
  for(int n=128;n;n>>=1)
    *binary++ =(ch&n)?'1':'0';
  *binary='\0';
}
/* converts a binary string representation into a character */
char binary_to_ascii(char*binary){
  int ch=0;
  for(int n=0,slide=128;n<8;n++,slide>>=1){
    if(binary[n]=='1')
      ch=ch|slide;
  }
  return ch;
}

// iterative
// void text_to_binary(const char* str, char* encoded){
//   char binary[512];
//   encoded[0]='\0';
//
//   for(size_t i=0;i<strlen(str);i++){
//     ascii_to_binary(str[i],binary);
//     strcat(encoded,binary);
//   }
// }

void text_to_binary_recursive(const char* text, char* binary){
  char bin_buf[512];

  ascii_to_binary(text[0],bin_buf);
  strcat(binary,bin_buf);

  if(strlen(text)>1)
    text_to_binary_recursive(&text[1],binary);
}

void text_to_binary(const char* text, char* binary){
  binary[0]='\0';
  text_to_binary_recursive(text,binary);
}

void binary_to_text(const char* encoded, char* text){
  char buf[512];

  for(size_t i=0;i<(strlen(encoded)/8);i++){
    strncpy(buf,encoded+(i*8),8);
    char ch=binary_to_ascii(buf);
    text[i]=ch;
    text[i+1]='\0';
  }
}

void add_error_correction(const char*data, char* correct){
  char c1,c2,c3;
  char data_buf[512],cor_buf[512];
  correct[0]='\0';

  for(int i=0;i<(strlen(data)/4);i++){
    strncpy(data_buf,data+(i*4),4);

    (data_buf[0]+data_buf[1]+data_buf[3])%2==0?c1='0':c1='1';
    (data_buf[0]+data_buf[2]+data_buf[3])%2==0?c2='0':c2='1';
    (data_buf[1]+data_buf[2]+data_buf[3])%2==0?c3='0':c3='1';

    cor_buf[0]=c1;
    cor_buf[1]=c2;
    cor_buf[2]=data_buf[0];
    cor_buf[3]=c3;
    cor_buf[4]=data_buf[1];
    cor_buf[5]=data_buf[2];
    cor_buf[6]=data_buf[3];
    cor_buf[7]='\0';

		strcat(correct,cor_buf);
  }
}

int decode(const char* received, char* decoded){
  char rec_buf[512],dec_buf[512];
  char p1,p2,p3;
  int pos,count=0;
  decoded[0]='\0';

  for(int i=0;i<(strlen(received)/7);i++){
    strncpy(rec_buf,received+(i*7),7);
    rec_buf[7]='\0';

    (rec_buf[3]+rec_buf[4]+rec_buf[5]+rec_buf[6])%2==0?p1=0:p1=1;
    (rec_buf[1]+rec_buf[2]+rec_buf[5]+rec_buf[6])%2==0?p2=0:p2=1;
    (rec_buf[0]+rec_buf[2]+rec_buf[4]+rec_buf[6])%2==0?p3=0:p3=1;

    if(!(p1==0 && p2==0 && p3==0)){
      count++;
      pos=p1*4+p2*2+p3;

      rec_buf[pos-1]=='0'?rec_buf[pos-1]='1':rec_buf[pos-1]='0';
    }

    dec_buf[0]=rec_buf[2];
    dec_buf[1]=rec_buf[4];
    dec_buf[2]=rec_buf[5];
    dec_buf[3]=rec_buf[6];
    dec_buf[4]='\0';

    strcat(decoded,dec_buf);
  }
  return count;
}
