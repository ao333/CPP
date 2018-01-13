#include <iostream>
#include <iomanip>
#include"convert.h"
using namespace std;

void print_preliminary_message();
void input_table_specifications(int&, int&, int&);
void print_message_echoing_input(int low, int high, int step);
void print_table(int low, int high, int step);
	
int main() {
  int fah, low, high, step;

  cout << setiosflags (ios::left);
  print_preliminary_message();
  input_table_specifications(low, high, step);
  print_message_echoing_input(low, high, step);
  print_table(low, high, step);

  return 0;}

void print_preliminary_message(){
  cout << "This temperature conversion program prompts the user for minimum and  maximum  bounds, and step to convert them fahrenheit into a table of celsius and absolute values\n";}

void input_table_specifications(int&low, int&high, int&step){
  cout << "Enter lower bound\n";
  cin >> low;
  cout << "Enter higher bound\n";
  cin >> high;
  cout << "Enter step\n";
  cin >> step;}

void print_message_echoing_input(int low, int high, int step){
  cout << low << " " << high << " " << step << "\n\n";}

void print_table (int low, int high, int step){
  cout.width(20);
  cout << "Fahrenheit";
  cout.width(20);
  cout << "Celsius";
  cout.width(20);
  cout << "Absolute Value\n\n";
		
  cout.setf(ios::fixed);
  cout.precision(2);

  int fah;
  for (fah=low; fah<=high; fah+=step) {
    cout.width(20);
    cout << fah;
    cout.width(20);
    cout << celsius_of(fah);
    cout.width(20);
    cout << absolute_value_of(fah) << "\n";}
}
