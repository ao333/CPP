#include<iostream>
#include<fstream>
using namespace std;

int main(){
  char ch;
  int count=0;
  ifstream in;

  in.open("blank.cpp");
  in.get(ch);

  while(!in.fail()){
    count++;
    in.get(ch);
  }
  cout << "Total chars including spaces is " << count << endl;
  in.close();
  return 0;
}
