#include <iostream>

using namespace std;

#define VERBOSE

class Employee {
private:
  double salary;
  // making a pure virtual or abstract method
  virtual double bonus_amount()=0;
  // double bonus_amount() { return 0; }
public:
  Employee(double _salary) : salary(_salary) {
  }
  void payrise() {
  #ifdef VERBOSE
    cout << "Employee(" << this << "): payrise called" << endl;
    cout << "Employee(" << this << "): salary before is " << salary <<
    endl;
  #endif
    salary += bonus_amount();
  #ifdef VERBOSE	
    cout << "Employee(" << this << "): salary is now " << salary << endl;
  #endif  
  }
};

class Manager : public Employee {
  
public:
  Manager(double _salary) : Employee(_salary) {
  }
  double bonus_amount() {
    return 100;
  }

};


class Executive : public Employee {
public:
  Executive(double _salary) : Employee(_salary) {
  }
  double bonus_amount() {
    return 300;
  }
};

int main() {

  Executive bill_gates(1);
  bill_gates.payrise();

  Employee &leader = bill_gates;
  leader.payrise();

  Employee *company[3];

  company[0] = new Manager(1000);
  company[1] = new Executive(2000);
  company[2] = new Manager(800);
  
  for (int n=0; n<3; n++)
    company[n]->payrise();

  for (int n=0; n<3; n++)
    delete company[n];

  return 0;
}
