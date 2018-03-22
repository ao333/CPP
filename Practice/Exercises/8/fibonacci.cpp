#include <iostream>
#include <cstdlib>
using namespace std;

int fibonacci(int number) {

  if (number==0)
    exit(1);
  if (number < 1) {
    cout << "fibonacci numbers can only be whole numbers >= 1\n";
    exit(1);
  }
  else if (number==1 || number==2)
    return 1;
  else
    return (fibonacci(number-1) + fibonacci(number-2));
}

int main() {
  int fib;

  while (fib != '0') {
    cout << "enter a whole number >= 1 or '0' to close program (non-whole-numbers will be rounded down to the nearest integer)\n";
    cin >> fib;
    cout << "fibonacci number is " << fibonacci(fib) << endl;
  }

  return 0;
}
