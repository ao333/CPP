#include <iostream>
using namespace std;
	
enum Day {Sun, Mon, Tue, Wed, Thu, Fri, Sat};

void print_day(Day count, ostream&cout);
int closing_time(Day day_of_the_week);

int main(){
  int count;
	
  cout.setf(ios::left);
  cout.width(17);
  cout << "DAY";
  cout << "CLOSING TIME\n\n";

  for (count = (int)Sun; count <= (int)Sat; count++){
    cout.width(19);
    print_day((Day)count, cout);
    cout << closing_time((Day)count) << "pm\n";}
	
  return 0;}

void print_day(Day count, ostream&cout){
  switch (count){
  case Sun: cout << "Sunday"; break;
  case Mon: cout << "Monday"; break;
  case Tue: cout << "Tuesday"; break;
  case Wed: cout << "Wednesday"; break;
  case Thu: cout << "Thursday"; break;
  case Fri: cout << "Friday"; break;
  case Sat: cout << "Saturday"; break;
  default: cout << "ERROR!";}}

int closing_time(Day count){
  switch (count){
  case Sun: return 1;
  case Wed: return 8;
  case Sat: return 5;
  default: return 6;}}
