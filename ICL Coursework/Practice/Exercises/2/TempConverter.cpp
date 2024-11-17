#include <iostream>
using namespace std;
	
int main() {
  
  int fah;
  int low;
  int high;
  int step;

  cout << "Enter Lowest Fahrenheit Temperature\n";
  cin >> low;
  cout << "Enter Highest Fahrenheit Temperature\n";
  cin >> high;
  cout << "Enter Desired Step Size\n";
  cin >> step;
  cout << "Low High Step: " << low" " << high" " << step"\n\n";
	
  cout.width(20);
  cout << "Fahrenheit";
  cout.width(20);
  cout << "Celsius";
  cout.width(20);
  cout << "Absolute Value\n\n";
		
  cout.setf(ios::fixed);          
  cout.precision(2);

  for (fah=low; fah<=high; fah+=step) {
    cout.width(20);
    cout << fah;
    cout.width(20);
    cout << (double)(fah-32)*5/9;
    cout.width(20);
    cout << (double)(fah-32)*5/9+273.15 "\n";
      }
  return 0;
}
