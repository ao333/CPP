#include <iostream>
#include <string>

using namespace std;

class Car;

class Passenger {
  private: // only instances of class Passenger can access this attribute
  double weight;
  string name;

  public: // public operations
  Passenger(string n, double w) { // constructor
    name = n; // (*this).name = n // this->name = n
    weight = w; 
  }

  void print_details(ostream &out) {
    out << name << " (" << weight << "kg)" << endl;
  }
  
  void diet();
  void eat(double food_weight) {
    cout << "Passenger(" << this << ") eat called." << endl;
    weight += food_weight;
  }
  bool get_into(Car &c);

  double get_weight() const { return weight; }

  friend ostream &operator<< (ostream &out, const Passenger &p);
};

ostream &operator<< (ostream &out, const Passenger &p) {
  out << "Passenger(" << &p << ") with name " << p.name << " and weight " << p.weight;
  return out;
}

void Passenger::diet()
{
  if (weight > 40) 
    weight -= 1.0;
}

class Car {
private:
  int mileage;
  string colour;
  bool engine_on;
  double weight;
  int passenger_count;
  Passenger *rider[3]; // rider is an array of 3 pointers to passengers
public:
  Car(int m, string c, double w);
  void start() {
    engine_on = true;
  }
  void stop() {
    engine_on = false;
  }
  bool drive() {
    mileage++;
  }
  bool take_passenger(Passenger &p) {
    if (passenger_count >= 3)
      return false;
    rider[passenger_count] = &p;
    passenger_count++;
    weight += p.get_weight();
    return true;
  }
};

Car::Car(int m, string c, double w)
{
  mileage = m; // implicitly this->mileage = m;
  colour = c;
  engine_on = false;
  weight = w;
  passenger_count = 0;
  for (int n=0; n<3; n++)
    rider[n] = NULL;
}

bool Passenger::get_into(Car &c) {
  return c.take_passenger(*this);
}

int main() {
  Passenger alice("Alice",60), bob("Bob", 70);

  Car bmw(10000,"Red",1200); // create Car instance on the stack

  Car *mini = new Car(50000,"Mini",750); // create Car instance on the heap

  alice.print_details(cout);

  alice.eat(5); //  alice is the receiver of the eat method call

  bob.eat(3); // now it's bob's turn
  
  cout << alice << endl;

  for (int days = 0; days<5; days++)
    alice.diet();

  cout << alice << endl;

  if (bob.get_into(bmw)) {
    cout << "let's go!" << endl;
  } else {
    cout << "sorry bob" << endl;
  }

  bob.get_into(bmw);
  bob.get_into(bmw);
    
  if (bob.get_into(bmw)) {
    cout << "let's go!" << endl;
  } else {
    cout << "sorry bob" << endl;
  }
  
  return 0;
}
