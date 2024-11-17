#include<iostream>
using namespace std;

enum Logical{False,True};

int validnumber();
Logical notprime(int integer);

int main(){
  int number;
  number=validnumber();
  
  while (number!=0){
    if (notprime(number))
      cout << "not prime\n";
    else
      cout << "prime\n";
    number=validnumber();}

  return 0;
}

int validnumber(){
  int number;

  do {cout << "input a prime integer between 1 and 1000 or 0 to end program: ";
    cin >> number;
    if (number <0 || number>1000)
      cout << "out of range, try again\n";
  } while (number <0 || number > 1000);

  return number;}

Logical notprime(int integer){
  for (int factor=2; factor<integer; factor++){
    if ((integer%factor)==0)
      return False;
  }
  return True;
}
