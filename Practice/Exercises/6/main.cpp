#include<iostream>
#include"IntegerArray.h"
using namespace std;

const int n = 5;

int main(){

  int a1[n];
  int a2[n];

  cout << "input a1 array\n";
  input_array(a1,n);
  cout << "\ninput a2 array\n";
  input_array(a2,n);

  cout << "\na1 array before copy\n";
  display_array(a1,n);
  cout << "\na2 array before copy\n";
  display_array(a2,n);

  copy_array(a1,a2,n);
  cout << "\na1 array after copy\n";

  display_array(a1,n);
  cout << "\na2 array after copy\n";
  display_array(a2,n);

  cout << "\nSD of a1: " << standard_deviation(a1,n) << endl;

  return 0;
}
