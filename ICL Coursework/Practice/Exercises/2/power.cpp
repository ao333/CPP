#include <iostream>
using namespace std;

int main() {
  double x=0, solution=0;
  int n=0, count=1;
  
  cout << "Input x\n";
  cin >> x;
  cout << "Input n\n";
  cin >> n;

  for (count = 0; count < n; count++)
    solution *=x;
  cout << solution << "\n";

  return 0;
}