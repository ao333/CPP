#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;


class Date {
private:
  int day, month, year;

  int days_since_01011970() const {
    // exploits C function mktime ("man mktime" for details)
    struct tm t;
    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    t.tm_sec = t.tm_min = t.tm_hour = 0;
    time_t t_seconds = mktime(&t);
    return ceil(t_seconds/86400.0);
  }
public:
  Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
  }

  // copy constructor
  Date(const Date &other) : day(other.day), month(other.month), year(other.year) {
  }
  
  // make global operator for outputting dates to streams
  // a friend of the class
  friend ostream &operator<<(ostream &out, const Date &d);

  //  operator belonging to class for subtracting dates
  int operator-(const Date &other) const {
    return days_since_01011970() - other.days_since_01011970();
  }

  //  friend int operator-(const Date &one, const Date &two);

  static Date today() {
    time_t rawtime;
    time(&rawtime);
    struct tm *t = localtime(&rawtime);
    assert(t);
    return Date(t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
  }
};

/*
int operator-(const Date &one, const Date &two)
{
  return one.days_since_01011970() - two.days_since_01011970();
}
*/

ostream &operator<<(ostream &out, const Date &d) {
  out << d.day << "/" << d.month << "/" << d.year;
  return out;
}

class Passenger {
private:
  string name;
  string address;
public:
  Passenger(string n, string a) : name(n), address(a) {
  }
};

class Flight {
private:
  int codeNumber;
  double price;
  Date takeoff;
public:
  Flight (Date d, int c, double p) : takeoff(d), codeNumber(c), price(p) {
  }
  Date getDate() const { return takeoff; }
  double getPrice() const { return price; }
};

class Booking {
protected:
  Flight *f;
  Passenger *p;
  string seat;
  
  virtual int days_before() = 0;
  virtual double cancel_amount() = 0;
public:
  Booking (Flight *_f, Passenger *_p, string _seat) {
    f = _f;
    p = _p;
    seat = _seat;
  }
  bool cancel() {
    if (f->getDate() - Date::today() < days_before())
      return false;
    double to_pay = cancel_amount();
    // do the paying
    return true;
  }
};

class FlexibleBooking : public Booking {
private:
  double amount_paid;
  int days_before() { return 10; }
  double cancel_amount() {
    return 0.8*amount_paid;
  }
public:
  FlexibleBooking(Flight *f, Passenger *p, string s, int ap) : Booking (f,p,s), amount_paid(ap) {
  }
};

class FirmBooking : public Booking { 
private:
  int days_before() { return 20; }
  double cancel_amount() {
    return f->getPrice();
  }
public:
  FirmBooking(Flight *f, Passenger *p, string s) : Booking (f,p,s) {
  }
};

int main() {

  Date xmas(25,12,2017);
  
  cout << "today is " << Date::today() << endl;
  // xmas.operator-(Date::today()) 
  cout << "days to xmas = " << xmas - Date::today() << endl;

  Passenger alice("Alice", "Queen's Tower, SW7 2AZ");
  Passenger bob("Bob", "Huxley Building, SW7 2RH");

  Flight ba249( Date(19,11,2017), 249, 399);
  cout << "flight is on " << ba249.getDate() << endl;

  cout << "days before = " << ba249.getDate() - Date::today() << endl;

  FlexibleBooking mybooking(&ba249, &alice, "1A", 100);
  FirmBooking yourbooking(&ba249, &bob, "16F");

  if (mybooking.cancel()) {
     cout << "Flexible booking cancelled!" << endl;
  } else
     cout << "Flexible booking could not be cancelled!" << endl;

  if (yourbooking.cancel()) {
     cout << "Firm booking cancelled!" << endl;
  } else
     cout << "Firm booking could not be cancelled!" << endl;
  return 0;
}

