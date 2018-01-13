#include <iostream>

using namespace std;

enum Weekday {MON, TUES, WED, THURS, FRI, SAT, SUN};

void print_weekday(Weekday w) {
  switch (w) {
  case MON:
    cout << "Monday"; break;
  case TUES:
    cout << "Tuesday"; break;
  default:
    cout << "Other day";
  }
  cout << endl;
}

ostream &operator<<(ostream &out, const Weekday &day) {

  switch (day) {
  case MON: 
    out << "Monday"; break;
  case TUES:
    out << "Tuesday"; break;
  case WED:
    out << "Wednesday"; break;
  case THURS:
    out << "Thursday"; break;
  default:
    out << "Some other day";
  }
  return out;
}

int main(){

  Weekday shopping_day = TUES;

  Weekday today = THURS;

  for (Weekday d = MON; d<=THURS; d = (Weekday) ((int) d + 1)) {
    //    cout << d << endl; // <-- operator<<(cout, d)
    print_weekday(d);
  }

  return 0;
}
