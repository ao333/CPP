#include <iostream>
#include <cstdlib>
using namespace std;

int greatest_common_divisor(int num1, int num2) {
  if (num1<1 || num2<1) {
    cout << "\nnegative input, exiting\n";
    exit(1);
  }
  else if (num1==num2)
    return num1;
  else if (num1<num2)
    return greatest_common_divisor(num1, (num2-num1));
  else
    return greatest_common_divisor(num2, (num1-num2));
}

int main(){
  int num1, num2;

  cout << "enter first whole number: ";
  cin >> num1;
  cout << "enter second whole number: ";
  cin >> num2;
  cout << "greatest common divisor is: " << greatest_common_divisor(num1, num2) << endl;

  return 0;
}
