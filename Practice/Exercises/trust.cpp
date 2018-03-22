#include<iostream>
#include<cmath>
using namespace std;

float f(){
  float a=77617, b=33096;
  cout << "float: " << (((333.75*pow(b,6) + pow(a,2)*(11*pow(a,2)*pow(b,2)-121*pow(b,4)-2)) + 5.5*pow(b,8))-pow(a,2)*pow(b,6))+a/(2*b) << endl;}
double d(){
  double a=77617, b=33096;
  cout << "double: " << (((333.75*pow(b,6) + pow(a,2)*(11*pow(a,2)*pow(b,2)-121*pow(b,4)-2)) + 5.5*pow(b,8))-pow(a,2)*pow(b,6))+a/(2*b) << endl;}
long double l(){
  long double a=77617, b=33096;
  cout << "float: " << (((333.75*pow(b,6) + pow(a,2)*(11*pow(a,2)*pow(b,2)-121*pow(b,4)-2)) + 5.5*pow(b,8))-pow(a,2)*pow(b,6))+a/(2*b) << endl;}

int main(){
  f();
  d();
  l();}

