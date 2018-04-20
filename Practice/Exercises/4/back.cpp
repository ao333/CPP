#include<iostream>
#include<fstream>
using namespace std;

int totalchar();
char charat(int index);

int main(){
  int count=totalchar();

  for (int index=count; index>0; index--)
    cout << charat(index);

  return 0;
}

int totalchar(){
  char ch;
  ifstream in;

  int count=0;

  in.open("back.cpp");
  in.get(ch);
  while(!in.fail()){
    count++;
    in.get(ch);
  }
  in.close();
  return count;
}

char charat(int index){
  char ch;
  ifstream in;

  in.open("back.cpp");

  for(int i=0; i<index; i++)
    in.get(ch);

  in.close();
  return ch;
}
