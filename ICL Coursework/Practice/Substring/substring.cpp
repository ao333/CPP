#include <iostream>
#include <cstring>
#include "substring.h"
using namespace std;

bool is_prefix(const char* sub, const char* str){
  if(strlen(sub)==0)
    return true;

  if(sub[0]==str[0]){
    char subcut[strlen(sub)];
    for(size_t i=1; i<=strlen(sub); i++)
      subcut[i-1]=sub[i];

    char strcut[strlen(str)];
    for(size_t i=1; i<=strlen(str); i++)
      strcut[i-1]=str[i];

    return is_prefix(subcut,strcut);
  }
  return false;
}

// int substring_position(const char* sub, const char* str){
//   size_t count=0;
//   if(is_prefix(sub,str))
//     return count;
//
//   while(count!=strlen(str)){
//     count++;
//
//     char strcut[strlen(str)];
//     for(size_t i=0; i<=strlen(str); i++)
//       strcut[i]=str[i+count];
//
//     if(is_prefix(sub,strcut))
//       return count;
//   }
//   return -1;
// }

int substring_position(const char* sub, const char* str){
  if(is_prefix(sub,str))
    return0;
  if(strlen(sub)>strlen(str))
    return-1;
  return (substring_position(sub,&str[1])==-1)?-1:substring_position(sub,&str[1])+1;
}
