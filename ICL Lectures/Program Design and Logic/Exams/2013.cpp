/*
2a \Imperial-Solutions\4 Program Design and Logic\1 Logic\3.4S Coursework

b i)
1. AX[P(X)->Q(X)]
2. ~EY[Q(Y)]
  3. EX[P(X)]            Assume
  4. P(a)->Q(a)          AE,1
    5. P(a)              Assume
    6. Q(a)              ->E,4,5
    7. EX[Q(X)]          EI,6
  8. EX[Q(X)]            EE,3,5,7
9. ~EX[Q(X)]             RAA,2,3,8

ii)
1. AX[P(X)->Q(X)]
2. AX[S(X)->M(X)vN(X)]
3. ~EX[Q(X)]
4. AX[N(X)->AY(R(Y)->P(Y)]
5. EX[R(X)->~EY(M(Y))]
6. P(a)->Q(a)              AE,1
7. S(a)->M(a)vN(a)         AE,2
8. N(a)->AY(R(Y)->P(Y)]    AE,4
  9. S(a)                 Assume
  10. M(a)vN(a)            ->E,7,9
    11. R(a)               Assume
    12. EX(R(X))           EI,11
	13. ~EY(M(Y))          ->E,5,12
	14. AY~(M(Y))          All False, None True,13
	15. ~M(a)              AE,14
	16. N(a)               vE,10,15
	17. AY(R(Y)->P(Y)      ->E,8,16
	18. R(a)->P(a)         AE,17
	19. P(a)               ->E,11,18
	20. EX(P(X))           EI,19
	21. ~EX(P(X))          i),21
  22. ~R(a)                RAA,11,20,21
23. S(a)->~R(X)            ->I,9,22
24. AX(S(X)->~R(X))        AI,23

3
#include<iostream>
#include<string>
#include<map>
using namespace std;

class Shop;

class Bicycle {
private:
	string id;
	string make;
	float price;
public:
	Bicycle(string i, string m, float p) :id(i), make(m), price(p) {};
	float get_price() { return price; }
};
class Customer {
private:
	string name;
	float account;
public:
	Customer(string n) :name(n), account(0) {};
	float get_acc() { return account; }
	void deposit(float a) { account += a; }
	void reduce(float a) { account -= a; }
	bool buy(Bicycle *b, Shop *s);
	bool service(Bicycle *b, Shop *s);
};
class Shop {
private:
	map<Bicycle*, Customer*> bc;
	map<Bicycle*, int> bi;
public:
	bool buy(Customer*, Bicycle*);
	bool service(Customer*, Bicycle*);
};

bool Customer::buy(Bicycle *b, Shop *s) { return s->buy(this, b); }
bool Customer::service(Bicycle *b, Shop *s) { return s->service(this, b); }

bool Shop::buy(Customer *c, Bicycle *b) {
	if (c->get_acc() < b->get_price()) return false;
	else {
		bc[b] = c;
		bi[b] = 0;
		c->reduce(b->get_price());
		return true;
	}
}
bool Shop::service(Customer *c, Bicycle *b) {
	if (bc[b] != c) return false;
	float charge = 0;
	if (bi[b] == 1) charge = 20;
	else if (bi[b] > 1) charge = 40;
	if (charge > c->get_acc()) return false;
	else {
		bi[b] += 1;
		c->reduce(charge);
		return true;
	}
}

int main() {
	Shop shop;
	Customer Lance("Lance");
	Lance.deposit(2000);
	Bicycle b1("TK15895", "Trek", 475);
	Bicycle b2("SSB2300", "Specialized", 1600);
	if (Lance.buy(&b1, &shop)) cout << "success buy b1" << endl;
	if (Lance.buy(&b2, &shop)) cout << "success buy b2" << endl;
	if (Lance.service(&b1, &shop)) cout << "success service b1" << endl;
	if (Lance.service(&b2, &shop)) cout << "success service b2" << endl;
}

4
*/

#include <iostream>
#include <string>
using namespace std;

class Competitor {
private:
	string name;
	int age;
public:
	Competitor(string, int);
	compete(Event *, int);
	compute();
};

class Event {
protected:
	float a, b, c;
public:
	Event(float, float, float);
	virtual float score(float) = 0;
};

class Run {
public:
	Run(float, float, float);
	virtual float score(float);
};

class Jump {
public:
	Jump(float, float, float);
	virtual float score(float);
};

class Throw {
public:
	Throw(float, float, float);
	virtual float score(float);
};

int main() {
	Event * 100m = new Run(9.23, 26.7, 1.835);
	Event* high = new Jump(1.85, 75, 1.348);
	Event* shot = new Throw(56.02, 1.5, 1.835);

	Competitor JE = new Competitor("Jessica Ennis", 28);

	JE->compete(100m, 12.54);
	JE->compete(high, 186);
	JE->compete(shot, 14.28);

	cout >> JE->compute();
}