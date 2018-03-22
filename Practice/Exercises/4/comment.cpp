#include<iostream>
#include<fstream>
using namespace std;

int main(){
  char character;
  char after;
  int inside = 0;
  ifstream in;
  ofstream out;

  /* test if comments have been removed  */
  cout << "testing; " << 16/2 << " = " << 4*2 << ".\n\n";

  in.open("comment.cpp");
  out.open("WithoutComments.cpp");
  in.get(character);

  while(!in.fail()){
    if(inside==0 && character=='/'){
      in.get(after);
      if(after=='*')
        inside=1;
      else
        in.putback(after);
      }
    if(inside==1 && character=='*'){
      in.get(character);
      if(character=='/'){
        inside=0;
        in.get(character);
      }
    }
    if(inside==0){
      out.put(character);
      cout << character;
    }
    in.get(character);
  }
  in.close();
  out.close();
  return 0;
}
