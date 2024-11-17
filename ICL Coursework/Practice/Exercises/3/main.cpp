#include<iostream>
#include"statistics.h"
using namespace std;

void inputtestnumber(int&testnumber);
void test1();
void test2();
void test3();
void test4();

int main(){
  int testnumber;
  
  cout << "This program tests the functions in the 'statistics.h' head file.\n";
  inputtestnumber(testnumber);

  while (testnumber!=0){
    if (testnumber==1)
      test1();
    else if (testnumber==2)
      test2();
    else if (testnumber==3)
      test3();
    else if (testnumber==4)
      test4();
    else
      cout << "Sorry, the program can only test 1, 2, 3 or 4 values.\n";
    inputtestnumber(testnumber);}

  cout << "Finished testing 'statistics.h' header file.\n";
  return 0;}

void inputtestnumber(int&testnumber){
  cout << "Do you wish to test 1, 2, 3 or 4 numbers (enter 0 to end the program): ";
  cin >> testnumber;
  cout << endl << endl;}

void test1(){
  double one;
  cout << "Enter first value: ";
  cin >> one;
  cout << "Average: " << avg(one) << ". Standard deviation: " << sd(one) << ".\n";}

void test2(){
  double one, two;
  cout << "Enter first value: ";
  cin >> one;
  cout << "Enter second value: ";
  cin >> two;
  cout << "Average: " << avg(one,two) << ". Standard deviation: " << sd(one,two) << ".\n";}

void test3(){
  double one, two, three;
  cout << "Enter first value: ";
  cin >> one;
  cout << "Enter second value: ";
  cin >> two;
  cout << "Enter third value: ";
  cin >> three;
  cout << "Average: " << avg(one,two,three) << ". Standard deviation: " << sd(one,two,three) << ".\n";}


void test4(){
  double one, two, three,four;  
  cout << "Enter first value: ";
  cin >> one;
  cout << "Enter second value: ";
  cin >> two;
  cout << "Enter third value: ";
  cin >> three;
  cout << "Enter fourth  value: ";
  cin >> four;
  cout << "Average: " << avg(one,two,three,four) << ". Standard deviation: " << sd(one,two,three,four) << ".\n";}
