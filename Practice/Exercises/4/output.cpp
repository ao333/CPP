#include<iostream>
#include<fstream>
using namespace std;

int main(){
  char character;
  ifstream in;

  in.open("output.cpp");
  in.get(character);

  while (!in.fail()){
    cout << character;
    in.get(character);
  }
  in.close();
  return 0;
}
