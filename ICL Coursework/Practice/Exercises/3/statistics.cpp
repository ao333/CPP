#include<iostream>
#include<cmath>
#include"statistics.h"
using namespace std;

double avg(double one){
  return one;}
double avg(double one, double two){
  return (one+two)/2;}
double avg(double one, double two, double three){
  return (one+two+three)/3;}
double avg(double one, double two, double three, double four){
  return (one+two+three+four)/3;}

double sd(double one){
  return 0;}
double sd(double one, double two){
  double e1, e2;
  e1 = (one - avg(one,two)) * (one - avg(one,two));
  e2 = (two - avg(one,two)) * (two - avg(one,two));
  return sqrt(avg(e1,e2));}
double sd(double one, double two, double three){
  double e1, e2, e3;
  e1 = (one - avg(one,two)) * (one - avg(one,two));
  e2 = (two - avg(one,two)) * (two - avg(one,two));
  e2 = (three - avg(one,two)) * (three - avg(one,two));
  return sqrt(avg(e1,e2,e3));}
double sd(double one, double two, double three, double four){
  double e1, e2, e3, e4;
  e1 = (one - avg(one,two)) * (one - avg(one,two));
  e2 = (two - avg(one,two)) * (two - avg(one,two));
  e2 = (three - avg(one,two)) * (three - avg(one,two));
  e2 = (four - avg(one,two)) * (four - avg(one,two));
  return sqrt(avg(e1,e2,e3,e4));}
