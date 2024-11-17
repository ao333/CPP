/*
2a
i) AA,ID[Applicant(ID,A)->ED(Apply(ID,D)^(D=MSc v D=MRes v D=PhD))]

ii) AID[Apply(ID,MRes)^Apply(ID,MSc)^ES,D,C(Dqual(ID,D,S,C))->Interview(ID)]^
    EID[(Apply(ID,PhD)^Interview(ID))^~AID(Apply(ID,PhD)->Interview(ID))]

iii) ~EID[Apply(ID,PhD)^~EC(Dqual(ID,MSc,CS,C)^(Interview(ID)vAccept(ID,PhD)))]

iv) AID,D[Accept(ID,D)->ED,S(Dqual(ID,D,S,1)^EA(Lqual(ID,Avg)^(A>=6.5)))]

v) AID,D[Accept(ID,D)<->(Accoffer(ID,D)vDefoffer(ID,D)vRejoffer(ID,D))]^
   AID,D[Billed(ID,D)<->(Accoffer(ID,D)vDefoffer(ID,D))]

b
vi) AID[Billed(ID,PhD)->EC(Dqual(ID,MSc,CS,C)^ED,S(ID,D,S,1))]
vii) Accept->Apply

1. AID,D[Billed(ID,D)<->(Accoffer(ID,D)vDefoffer(ID,D))] ^E,v)
2. Billed(a,PhD)<->Accoffer(a,PhD)vDefoffer(a,PhD)             AE,1
3. Billed(a,PhD)->Accoffer(a,PhD)vDefoffer(a,PhD)              <->E,2
  4. Billed(a,PhD)                                             Assume
  5. Accoffer(a,PhD)vDefoffer(a,PhD)                           ->E,3
  6. AccOffer(a,PhD)vDefoffer(a,PhD)vRejoffer(a,PhD)           vI,5
  7. Accept(a,PhD)                                             <->,v)
  8. Accept(a,PhD)->ES(Dqual(a,d,S,1)                          AE,iv)
     ^EAvg(Lqual(a,Avg)^(A>=6.5)))
  10. Accept(a,PhD)->ES,D(Dqual(a,D,S,1))                      ^E,9
  11. ES,D(Dqual(a,D,S,1)                                      ->E,8,10

  12. ~EID[~EC(Dqual(ID,MSc,CS,C)]                             ^E,iii)
  13. AID~~EC(Dqual(ID,MSc,CS,C))                              All False = None True
  14. AID,EC(Dqual(ID,MSc,CS,C))                               float Negation
  15. EC(Dqual(a,MSc,CS,C))                                    AE,14
  
  16. EC(Dqual(a,MSc,CS,C)^ES,D(a,D,S,1))                      ^I,11,15
17. Billed(a,PhD)->EC(Dqual(a,MSc,CS,C)^ED,S(a,D,S,1))         ->I,3,4,11,15,16
18. AID[Billed(ID,PhD)->EC(Dqual(ID,MSc,CS,C)^ED,S(ID,D,S,1))] AI,17

ii)
1. AX[P(X)<->Q(X)]
2. AX[Q(X)vR(X)->EY(S(X,Y))]
3. AX,Y[S(X,Y)->T(X,Y)]
4. AX,Y~[T(X,Y)^M(X,Y)]
5. P(a)<->Q(a)               AE,1
6. Q(a)vR(a)->EY(S(a,Y))     AE,2
7. S(a,b)->T(a,b)            AE,3
8. ~T(a,b)^M(a,b)            AE,4
9. P(a)->Q(a)                <->E,5
10. Q(a)->P(a)               <->E,5
  11. P(a)                   Assume
  12. Q(a)                   <->,5
  13. Q(a)vR(a)              vI,12
  14. EY[S(a,Y)]             ->E,6,13
    15. S(a,b)               Assume
	16. T(a,b)               ->E,7,15
  17. T(a,b)                 EE,14,15,16
  18. ~M(a,b)                ^E,8
  19. EY~M(a,Y)              EI,18
20. P(a) -> EY~M(a,Y)        I->11,19

4
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Nut {
private:
	float weight;
public:
	Nut(float _weight) :weight(_weight) {};
	virtual float get_fatpercent() = 0;
	float get_fat() { return weight * get_fatpercent(); }
	float get_kcal() {
		int fat = get_fat();
		return fat * 9 + (weight - fat) * 4;
	}
};

class Walnut : public Nut {
public:
	Walnut(float _weight) : Nut(_weight) {};
	float get_fatpercent() { return 0.6521; }
};

class Almond : public Nut {
public:
	Almond(float _weight) :Nut(_weight) {};
	float get_fatpercent() { return 0.5064; }
};

class Label {
private:
	string text;
public:
	Label(string _text) :text(_text) {};
};

class Bag {
private:
	int limit_size;
	vector<Nut*> nuts;
	Label *label;
public:
	Bag(int _limit) : limit_size(_limit) { label = NULL; }
	bool add(Nut *nut) {
		if (nuts.size() > limit_size) return false;
		nuts.push_back(nut);
	}
	string getBNI() {
		float fat = 0; float kcal = 0;
		for (int i = 0; i < nuts.size(); i++) {
			fat += nuts[i]->get_fat();
			kcal += nuts[i]->get_kcal();
		}
		return "Total of " + to_string(kcal) + " kcal (" + to_string(fat) + " g fat) " + (fat > 20 ? "[high in fat]" : "");
	}
	void add_label(Label *l) { label = l;}
};

int main() {
	Bag bag(5);
	Walnut w1(8);
	Almond a1(1.5);
	bag.add(&w1);
	bag.add(&a1);
	// cout << bag.getBNI() << endl;
	Label label(bag.getBNI());
	bag.add_label(&label);
	
	Walnut w2(13);
	bag.add(&w2);
	Label label2(bag.getBNI());
	bag.add_label(&label2);
}