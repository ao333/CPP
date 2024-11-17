/*
1a
i) EX,Y[day(X)^eve(Y)]

ii) AP,X[teaches(P,X)^day(X)^(~EC(teaches(P,C)^eve(C)) -> salary(P,sd)]^
AP,X[teaches(P,X)^day(X)^eve(X) -> salary(P,sde)]^
AP,X[teaches(P,X)^eve(X)^(~EC(teaches(P,C)^day(C)) -> salary(p,se)]

iii) AC,Sub[eve(C)^subject(Sub,C)->(type(Sub,languages) v type(Sub,humanities)]^
ASub[EC(eve(C)^subject(Sub,C)->type(Sub,languages) v type(Sub,humanities))]^
~EC[subject(latin,C)^(day(C) v eve(C))]

iv) ASub,C,S[enrolled(Sub,C)^day(C)^subject(Sub,C)->sitsExam(S,Sub)]^
ASub,S[EC(enrolled(S,C)^subject(Sub,C)^eve(C)^~EC(enrolled(S,C)^subject(Sub,C)^day(C))->~sitsExam(S,Sub))]

b
i) Start from S1 to arrive at S4
AX,T[~(exit(X,T)^~paid_for(X,T)) v stolen(X,T)]    Implication
AX,T[~exit(X,T) v ~~paid_for(X,T) v stolen(X,T)]   De Morgan
AX,T[~exit(X,T) v paid_for(X,T) v stolen(X,T)]     Double Negation
AX,T[stolen(X,T) v (~exit(X,T) v paid_for(X,T))]   Associative
AX,T[~stolen(X,T) -> (~exit(X,T) v paid_for(X,T))] Implication

ii) S3
AX,T[~(paid_for(X,T) v stolen(X,T) v exit(X,T)]   Implication
AX,T[~paid_for(X,T)^~stolen(X,T) v exit(X,T)]     Implication
~EX,T[~(~paid_for(X,T)^~stolen(X,T) v exit(X,T))] All True, None False Equivalence
~EX,T[~(~paid_for(X,T)^~stolen(X,T))^~exit(X,T)]  De Morgan
~EX,T[(paid_for(X,T) v stolen(X,T))^~exit(X,T)]   De Morgan

iii) A unless B: ~B->A/BvA
AI,Y,T[(approved(Y,I,T)^authorized(Y))v(exit(I,T)^~paid_for(I,T)->stolen(I,T))]^
AX[authorized(X)<->manager(X) v depManager(X)]

3
#include <iostream>
#include <string>
#include <list>
using namespace std; 

class User {
private:
	float x;
	float y;
	int credits;
public:
	User(float a, float b, int c) : x(a), y(b), credits(c) {}
	bool broadcast(string t, int r, list<User> userList);
	void move(float x, float y);
	void buy_credits(int credits);
	void get_credits();
};

bool User::broadcast(string t, int r, list<User> userList) {
	for (list<User>::iterator it = userList.begin(); it != userList.end(); it++) {
		if (credits <= 0) return false;
		if (it->x == x || it->y == y) continue; // skip source
		if (x > it->x + r) credits--;
		else if (y > it->y + r) credits--;
	}
	return true;
}
void User::move(float a, float b) {
	x = a;
	y = b;
};
void User::buy_credits(int c) {
	credits += c;
}
void User::get_credits() {
	cout << credits << endl;
}

int main() {
list<User> userList;
User Alice(3.5, 0.5, 5);
User Bob(10.0, 5.0, 5);
User Charles(10.0, 5.0, 5);

userList.push_back(Alice);
userList.push_back(Bob);
userList.push_back(Charles);

Alice.broadcast("Hello!", 10, userList);
Alice.move(3.0, 3.0);

Alice.get_credits();

Charles.broadcast("Come to my part at Royal Albert Hall", 5, userList);

Bob.buy_credits(10);
}

4
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Car {
private:
	string model;
	int cmass;
	Engine *engine;
	Driver *driver;
public:
	Car(string a, int b, Engine* c, Driver* d) : model(a), cmass(b), engine(c), driver(d) {}
	int racing_time(int distance, int min);
};

class Engine {
public:
	int power;
	int cylinder;
	string name;
	int emass;
	Engine(string a, int b, int c, int d) : name(a), emass(b), power(c), cylinder(d) {}
};

class Driver {
private:
	string name;
public:
	int dmass;
	Driver(string a, int b) : name(a), dmass(b) {};
};

int Car::racing_time(int distance, int min) {
	int totalMass = cmass + engine->emass + driver->dmass;
	if (totalMass > min) totalMass = min;
	if (engine->name == "TuboCharge2000") return (totalMass*distance*(1 - log(1 + exp(-distance))) / (engine->power*engine->cylinder ^ 2));
	else if (engine->name == "SupermanV3") return sqrt((2 * totalMass*distance) / (engine->power*engine->cylinder));
}

int main() {
	int min = 642;

	Driver *LH = new Driver("Lewist Hamilton", 67);

	Engine *TC2000 = new Engine("TuboCharge2000", 91, 250, 5);
	Car NR("NR-14", 582, TC2000, LH);
	NR.racing_time(1000, min);

	Engine *SMV3 = new Engine("SupermanV3", 87, 175, 4);
	Car TFD2("TFD-2", 411, SMV3, LH);
	TFD2.racing_time(1500, min);
}