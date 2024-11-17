/*
2a
i)
~Pv(Q->R) Implication
~Pv(~QvR) Implication
(~Pv~Q)vR Cummulative
~(P^Q)vR  Demorgan
P^Q->R    Implication

ii)
Natural Deduction
1. [A->(B->C)]->[(A->(C->D))->(A->(B->D))]
  2. (A->(B->C))^((A->(C->D)) Assume
  3. A->(B->C)                ^E,1
  4. A->(C->D)                ^E,1
  5. A^B->C                   i),3
  6. A^C->D                   i),4
    7. A^B                    Assume
    8. A                      ^E,7
    9. C                      ->E,5
    10. A^C                   ^I,8
    11. D                     ->E,5,10
  12. A^B->D                  ->I,7,11
  13. A->(B->D)               i),12
14. (A->(B->C))^((A->(C->D))->(A->(B->D)) ->I,2,13
15. (A->(B->C))->[(A->(C->D))->(A->(B->D))] i),14

Equivalence
~[A->(B->C)]v[(A->(C->D))->(A->(B->D))] Implication
~[~Av(B->C)]v[~(A->(C->D))v(A->(B->D))] Implication
~[~Av(B->C)]v[~(~Av(C->D))v(~Av(B->D))] Implication
~[~Av(~BvC)]v[~(~Av(~CvD))v(~Av(~BvD))] Implication
[A^~(~BvC)]v[(A^~(~CvD))v(~Av~BvD))]    Demorgan and Negation
[A^(B^~C)]v[(A^(C^~D))v(~Av~BvD))]      Demorgan and Negation
(A^B^~C)v[(A^C^~D)v~Av~BvD]             Commutative
A^[(B^~C)v(C^~D)]v~Av~BvD               Distributive
(~AvA)^[~Av((B^~C)v(C^~D))]v~BvD        Distributive
~Av(B^~C)v(C^~D)v~BvD                   Tautology
~Av(~BvB^~Bv~C)v(DvC^Dv~D)              Distributive
~Av~Bv~CvDvC                            Tautology
~Av~BvDv1                               Tautology
1                                       Simplification

b
i) AM,A[M(M)^A(A)->EM(M,A)]^
   ED[D(D)^AM(M(M)^EM(D,M)]

ii) AC[C(C)^~SC(C)->EM1,M2(Sign(M1,C)^Sign(M2,C)^~(M1=M2)^
    ~EX,Y,Z(Sign(X,C)^Sign(Y,C)^Sign(Z,C)^~(X=Y)^~(Y=Z)^~(X=Z))]^

	AC[C(C)^SC(C)->ED(Sign(D,C))^
	~ED1,D2(Sign(D1,C)^Sign(D2,C)^~(D1=D2))]

iii) AC,D[C(C)^D(D)^Sign(D,C)->
     (EM(M(M)^App(D,M,C))]v
	 EA(A(A)^WorksFor(A,D)^Delegate(D,C,A)^Sign(D,C)))]

3
class Tag {
private:
	int number; string name; System *system;
public:
	Tag(int, string, System&);
	void transmit(int, int, int);
};
class Area {
private:
	int x_low, y_low, x_high, y_high;
public:
	Area(int, int, int, int);
};
class System {
private:
	Table<Tag, Area> tag_areas;
public:
	System(Table<Tag, Area>);
	void receive(Readign& r, Tag& t);
};
class Reading {
private:
	int x_position, y_position, battery;
public:
	Reading(int, int, int);
};

Table tag_areas();
System *system = new System(tag_areas);

Area* l_area = new Area(0, 0, 5, 5);
Tag* lassie = new Tag(111, "Lassie", system);

system->tag_areas.set(lassie, l_area);

lassie.transmit(3, 3, 15);

Area::Area(int xl, int yl, int xh, int yh) {
	x_low = xl; x_high = xh; y_low = yl, y_high = yh;
}
Tag::Tag(int _number, int _name, System &s) {
	number = _number; name = _name; system = s;
}
System::System(Table _tag_table) {
	tag_table = _tag_table;
}
Reading::Reading(int x, int y, int _battery) {
	x_position = x; y_position = y; battery = _battery;
}

void Tag::Transmit(int x_pos, int y_pos, int battery) {
	Reading * reading = new Reading(x_pos, y_pos, battery);
	system->receive(reading, this);
}

void System::receive(Reading &r, Tag& t) {
	Area * area_to_check = tag_areas.get(t);
	if (r->x_pos < t->x_low || r->x_pos > t->x_high ....)
		cout << t->name << " out of area";
	if (r->battery < 20)
		cout << t->name << "'s battery is low";
}

int main() {
	Table <Tag*, Animal*> myTable;
	Animal* lassie = new Animal("Lassie", 0, 0, 5, 5);
	Tag * 111 = new Tag(111);
	myTable.set(111, lassie);

	Animal* garfield = new Animal("Garfield", 3, 4, 7, 8);
	Tag * 222 = new Tag(222);
	myTable.set(222, garfield);

	111->transmit(myTable.get(111), 3, 3, 15);
	222->transmit(myTable.get(222), 8, 8, 50);
}

4
*/

#include <iostream>
#include <string>
using namespace std;

class Battery {
private:
	double max, available, rechargeP;
public:
	Battery(double, double);
	void use(double);
	void recharge(double);
	double get_charge();
};
class Device {
private:
	Battery * battery;
public:
	Device(Battery*);
	virtual void operate(double) = 0;
	void recharge(double);
	double ant_life();
};
class Phone : public Device {
private:
	int cores, tasks;
public:
	Phone(Battery*, int);
	virtual void operate(double);
	void set_tasks(int);
};
class Camera : public Device {
private:
	int consumption;
public:
	Camera(Battery*);
	virtual void operate(double);
};

int main() {
	Battery * b1 = new Battery(6000, 500);
	Device * Canon = new Camera(b1);
	Canon->operate(1.5);
	Canon->recharge(0.5);
	cout << Canon->ant_life();
	Battery * b2 = new Battery(4000, 800);
	Device * Samsung = new Phone(b2, 2);
	Samsung->set_tasks(3);
	Samsung->operate(2);
	cout << Samsung->ant_life();
}

Battery::Battery(double a, double b) :max(a), rechargeP(b) {
	available = max;
}
void Battery::use(double a) { //a here is amount consumed
	if (a>available)
		available = 0;
	else
		available -= a;
}
void Battery::recharge(double t) {
	if (t*rechargeP + available > max)
		available = max;
	else
		available += t * rechargeP;
}
double Battery::get_charge() {
	return available;
}

Device::Device(Battery* b) : battery(b) {}
void Device::recharge(double t) {
	this.battery->recharge(t);
}
double Device::ant_life() {
	return battery->get_charge();
}

Phone::Phone(Battery* b, int a) :Device(b), cores(a) {
	tasks = 0;
}
void Phone::set_tasks(int a) {
	tasks = a;
}

void Phone::operate(double t) {
	if (cores>tasks)
		battery->use(tasks*t * 500 + 500);
	else
		battery->use(cores*t * 500 + 500);
}

Camera::Camera(Battery * b) :Device(b) {
	consumption = 1500;
}
void Camera::operate(double t) {
	battery->use(t*consumption);
}