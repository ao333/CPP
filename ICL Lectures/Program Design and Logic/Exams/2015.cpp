/*
1a
X->Y=~XvY
[(P->Q)^(R->S)^(PvR)]->(QvS)
[(~PvQ)^(~RvS)^(PvR)]->(QvS)
~[(~PvQ)^(~RvS)^(PvR)]v(QvS)
[(P^~Q)v(R^~s)v~(PvR)]v(QvS)         De Morgan
(P^~Q)v(R^~S)v~(PvR)v(QvS)           Associative
(P^~Q)v(R^~S)v~(PvR)v Q v S          Commutative
(P^~Q)vQv(R^~S)vSv~(PvR)
[(QvP)^(Qv~Q)]v[(RvS)^(Sv~s)]^~(PvR) distributive
(QvP)v(rvs0v~(PvR)                   X*True=X
QvPvRvSv~(PvR)                       Associative
QvSv(PvR)v~(PvR)                     Xv~X/True/Tautology

2a
i) EX,Y[tubeline(X)^tubeline(Y)^~(X=Y)^~EA,B,C(tubeline(A)^tubeline(B)^tubeline(C)^~(A=B)^~(B=C)^~(A=C)]
   ^AS[onNet(S)->EX(tubeline(X)^servedBy(S,X)]
   ^ES[onNet(S)^EX(tubeline(X)^servedBy(S,X))^~EA,B(tubeline(A)^tubeline(B)^servedBy(S,A)^servedBY(S,B)^~(A=B))]

ii) AL[tubeline(L)->ES1,S2(onNet(S1)^onNet(S2)^servedBy(S1,L)^servedBy(S2,L)^~(S1=S2)]
    ^AX,Y,S[tubeline(X)^tubeline(Y)^~(X=Y)^posChange(X,Y,S)<->onNet(S)^servedBy(S,X)^servedBY(S,Y)]

iii) AV,P[~(validTravelDoc(V,P)^possess(P,V))->EL~(tubeline(L)^travel(P,L))]

iv) AV,P(validTravelDoc(V,P)<->(freedomPass(V)^over65(P)) v dayTicket(V) v seasonTicket(V)

b
1. AS1,S2,C1,C2[cost(S1,S2,C1)^cost(S2,S1,C2)->C1=C2]
2. AS1,S2,S,C1,C2[hub(S1)^~hub(S2)^cost(S1,S,C1)^cost(S2,S,C2)->C1>C2]
3. hub(a)
4. ~hub(b)
5. cost(b,a,10)
6. cost(a,b,c)                                  Assume
7. hub(a)^hub(b)^cost(a,b,c)^cost(b,a,10)->c>10 AE,2
8. hub(a)^hub(b)^cost(a,b,c)^cost(b,a,10)       ^I,3,4,5,6
9. c>10                                         ->E,7,8
10. cost(a,b,c)^cost(b,a,10)->c=10              AE,1
11. cost(a,b,c)^cost(b,a,10)                    ^I,5,6
12. c=10                                        ->E,10,11
13. c>10^c=10                                   Inconsistent,9,12

3 \4 Program Design and Logic\2 Object Oriented Design & Programming\2 Object Oriented Design & Programming\4.2S Security Guards

4
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Component;
class Laptop;

class Employee {
private:
	string name;
	Laptop *laptop;
	static float budget;
public:
	Employee(string n) :name(n) { laptop = NULL; }
	bool order(Laptop *l);
	bool addComponent(Component *c);
	float getPerformance();
};
class Laptop {
private:
	float base_cost;
	vector<Component*> coms;
public:
	Laptop(float b) :base_cost(b) {};
	float get_price();
	void add(Component *c);
	float getPerformance();
};
class Component {
protected:
	float price;
	string make;
public:
	Component(float p, string m) :price(p), make(m) {};
	virtual float score() = 0;
	float get_price() { return price; }
};

class RAM :public Component {
private:
	float size;
public:
	RAM(float p, string m, float s) :Component(p, m), size(s) {};
	float score();
};
class IO : public Component {
private:
	float time;
public:
	IO(float p, string m, float t) :Component(p, m), time(t) {};
	float score();
};

bool Employee::order(Laptop *l) {
	if (l->get_price() > budget) return false;
	laptop = l;
	return true;
}
bool Employee::addComponent(Component *c) {
	if (laptop->get_price() + c->get_price() > budget) return false;
	laptop->add(c);
	return true;
}
float Employee::getPerformance() { return laptop->getPerformance(); }
float Employee::budget = 850;

float Laptop::get_price() {
	float sum = 0;
	for (int i = 0; i < coms.size(); i++) sum += coms[i]->get_price();
	return sum + base_cost;
}
float Laptop::getPerformance() {
	if (coms.size() == 0) return 100;
	float per = 0;
	for (int i = 0; i < coms.size(); i++) per += coms[i]->score();
	return per;
}
void Laptop::add(Component *c) {coms.push_back(c); }

float RAM::score() { return size * 8 + price * 0.1; }
float IO::score() { return price * 0.2 + (50 / time); }

int main() {
	Employee Andrew("Andrew");
	Laptop laptop(500);
	RAM r1(90, "Crucial", 8);
	RAM r2(90, "Crucial", 8);
	IO i1(150, "Samsung", 5.5);
	laptop.add(&r1);
	laptop.add(&r2);
	laptop.add(&i1);
	Andrew.order(&laptop);
	cout << Andrew.getPerformance() << endl;
	RAM r3(50, "Corsair", 4);
	Andrew.addComponent(&r3);
	cout << Andrew.getPerformance() << endl;
}