/*
2a i) iii)
S1 M^H->P
~(M^H)vP
~Mv~HvP
S3 ~(M^H^~P)
~Mv~HvP
S4 ~Mv(~HvP)
~Mv~HvP

S2 M^~H->~P
~(M^~H)v~P
~MvHv~P
S5 ~Mv~(~H^P)
~MvHv~P

ii) M^H->P (First Group)

b
i) AID,C,I,Q,T[Order(ID,C,I,Q,T)->ET1(T<T1^(process(ID,C,I,Q,T1) v apology(ID,C,T1))]

ii) AID,C,I,Q,T[Process(ID,C,I,Q,T)<->Invoice(ID,C,T)^dispatch(ID,C,T)]

iii) AID,C,I,Q1,Q2,T[Order(ID,C,I,Q1,T)^Instock(I,Q2,T)^(Q1<=Q2)->~Apology(ID,C,T)]

iv) AC,T[Owes(C,T)->~EID,I,Q(Order(ID,C,I,Q,T)^dispatch(ID,C,T))]

v) AC,T[ET1,ID(Invoice(ID,C,T1)^(T1<T)^~ET2(Paid(ID,C,T2)^(T1<T2)^(T2<=T)->Owes(C,T)]

vi) AD[wellman(D)<->AI,T(sells(D,I)->EQ(Instock(I,Q,T)^(Q>0)))]

3
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

class ship;

class System {
private:
	vector<Ship*> ships;
public:
	void broadcast(Ship *s) { for(int i = 0; i < ships.size(); i++) if (ships[i] != s) s->broadcastTo(ships[i]); }
	void add(Ship * p) { ships.push_back(p); }
};

class Ship {
private:
	string sign;
	float range;
	float lat;
	float lon;
	System *system;
	bool em;
public:
	Ship(string _sign, float _range, float _lat, float _lon, System * _system) : sign(_sign), range(_range), lat(_lat), lon(_lon), system(_system) { system->add(this); };
	void emergency() { em = true; }
	void update(float _lat, float _lon) { lat = _lat, lon = _lon; }
	void broadcast() { if(em) system->broadcast(this); }
	void broadcastTo(Ship *p) {
		float distance = getDistance(this, p);
		if (distance <= range) p->receive(this);
	}
	void receive(Ship *p) { cout << "RECEIVE MAYDAY FROM " << p->sign << endl; }
	static float getDistance(Ship *p1, Ship *p2) {
		return 2 * 3956 * asin(sqrt(hav(rad(p1->lat - p2->lat) + cos(rad(p1->lat))) * cos(p2->lat) * hav(rad(p1->lon - p2->lon))));
	}
	static float hav(float theta) { return sin(theta / 2) * sin(theta / 2);}
	static float rad(float alpha) { return 3.14 * alpha / 180;}
};

int main() {
	System system;
	Ship endeavour("2FBA7", 20, 36.158, -5.357, &system);
	Ship seaswan("2CEU8", 10, 36.180, -5.390, &system);
	seaswan.emergency();
	seaswan.broadcast();
	endeavour.update(36.179, -5.391);
}

4
*/

#include<iostream>
#include<string>
#include<stack>
using namespace std;

class AF;

class HR {
private:
	string name;
	string birth;
	int traySize;
	stack<AF*> afs;
public:
	HR(string _name, string _birth, int _size) :name(_name), birth(_birth), traySize(_size) {};
	bool add(AF *af);
	int get_num() { return afs.size(); }
	void remove();
};

class AF {
protected:
	string name;
	string birth;
	float OSmark;
public:
	AF(string _name, string _birth, float _OSmark) :name(_name), birth(_birth), OSmark(_OSmark) {};
	virtual float get_mark() = 0;
};

class NAF : public AF {
private:
	float CNmark;
public:
	NAF(string _name, string _birth, float _OSmark, float _CNmark) :AF(_name, _birth, _OSmark), CNmark(_CNmark) {};
	float get_mark() { return (OSmark + CNmark) / 2; }
};

class PAF : public AF {
private:
	float Pmark;
public:
	PAF(string _name, string _birth, float _OSmark, float _Pmark) :AF(_name, _birth, _OSmark), Pmark(_Pmark) {};
	float get_mark() { return (OSmark + Pmark) / 2; }
};

bool HR::add(AF *af) {
	if (afs.size() < traySize) {
		afs.push(af);
		return true;
	}
	return false;
}

void HR::remove() {
	stack<AF*> temp;
	while (afs.size() > 0) {
		AF *af = afs.top();
		if (af->get_mark() >= 66)
			temp.push(af);
		afs.pop();
	}
	afs = temp;
}

int main() {
	HR Helen("Helen", "1975", 50);
	NAF Peter("Peter", "1986", 65, 75);
	PAF Susan1("Susan", "1989", 70, 80);
	NAF Susan2("Susan", "1989", 70, 60);
	Helen.add(&Peter);
	Helen.add(&Susan1);
	Helen.add(&Susan2);
	Helen.remove();
	cout << Helen.get_num() << endl;
}