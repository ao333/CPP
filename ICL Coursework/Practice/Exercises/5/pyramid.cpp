#include<iostream>
using namespace std;

int validheight();
void print_pyramid(int height);

int main(){
  int height=validheight();
  
  cout << "This program prints a 'pryammid' shape of a specified height on the screen.\n\n";
  print_pyramid(height);}

int validheight(){
  int height;

  cout << "how high would you like the pryamid?: ";
  cin >> height;
  while (height<1 || height>30){
    cout << "Pick another height (must be between 1 and 30): ";
    cin >> height;}

 return height;}

void print_pyramid(int height){
  int const margin = 10;

  for (int row=1; row<=height; row++){
    for (int space=1; space<=margin+height-row; space++){
      cout << " ";}			   
    for (int star=1; star<=row*2; star++){
      cout << "*";}
    cout << endl;}
}
