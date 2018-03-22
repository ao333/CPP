#include <iostream>
#include <cstring>

using namespace std;

struct Student {
  char name[80];
  int age;
  double mark;
  Student *partner;
};

struct University {
  Student students[100];
};

int main() {

  Student susan = {"Susan",25,75,NULL}, bob= {"Bob",25,35,&susan};

  strcpy(susan.name, "Susan");
  susan.age = 25;
  susan.mark = 75;
  susan.partner = NULL;

  strcpy(bob.name, "Bob");
  bob.age = 25;
  bob.mark = 35;
  bob.partner = &susan;

  susan.partner = &bob;
  // (*(bob.partner)).partner = &bob;
  //  (bob.partner)->partner = &bob;

  Student *ptr = &bob;
  ptr->mark = 38; // ( (*ptr).mark = 38 )

  cout << susan.age << endl;

  cout << ( *(bob.partner)).age << endl;

  cout << bob.partner->age << endl;

  Student progclass[10];
  strcpy(progclass[0].name, "Anna");
  progclass[0].mark = 99;

  Student *p = new Student;
  strcpy( p->name, "Charles" );
  strcpy( (*p).name, "Charles" );
  p->age = 46;
  p->mark = 85;
  p->partner = NULL;



  p = &bob;

  cout << (*p).age << endl;

  cout << p->age << endl;

  return 0;
}
