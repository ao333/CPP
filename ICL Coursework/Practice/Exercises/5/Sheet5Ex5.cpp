#include<iostream>
#include<fstream>
using namespace std;

int counter(char letter);

int main(){
  char letter;

  cout.setf(ios::left);
  cout.width(20);
  cout<<"CHARACTER";
  cout<<"OCCURRENCES\n\n";

  for(letter='a';letter<='z';letter++){
    cout.width(20);
    cout<<letter;
    cout<<counter(letter)<<endl;
  }

  return 0;
}

int counter(char letter){
  char character;
  ifstream in;

  in.open("Sheet5Ex5.cpp");
  in.get(character);

  int count=0;
  while(!in.fail()){
    if(character==letter)
    count++;
    in.get(character);
  }
  in.close();

  return count;
}
