#include <iostream>
using namespace std;

int main()
{
  char letter;

  cout << "Type a letter\n";
  cin >> letter;

  if (letter >= 97 && letter <= 122){
    cout << "The upper case character corresponding to " << letter << " is " << (char) (letter - 32) << "\n";}
  else if (letter >=65 && letter <= 90){
    cout << "The lower case character corresponding to " << letter << " is " << (char) (letter + 32) << "\n";}
  else {
    cout << letter << " is not a letter\n";}

  return 0;
}
