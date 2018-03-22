#include<cmath>
#include<iostream>
#include"IntegerArray.h"
using namespace std;

void input_array(int a[], int n){
  for (int i = 0; i < n; i++) {
    cout << "input value for index " << i << endl;
    cin >> a[i];
  }
}

void display_array(int a[], int n){
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";

  cout << endl;
}

void copy_array(int a1[], int a2[], int n) {
  for (int i = 0; i < n; i++)
    a1[i] = a2[i];
}

float average (int a[], int n) {
  float sum;

  for (int i = 0; i < n; i++)
    sum += (float)a[i];

  return (sum/n);
}

float average (float a[], int n) {
  float sum;

  for (int i = 0; i < n; i++)
    sum += a[i];

  return (sum/n);
}

float standard_deviation (int a[], int n){
  float var[999];

  float avg = average(a,n);
  for (int i = 0; i < n; i++)
    var[i] = (a[i] - avg) * (a[i] - avg);
  return sqrt(average(var,n));
}
