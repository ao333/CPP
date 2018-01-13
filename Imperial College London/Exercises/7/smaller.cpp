#include <iostream>
using namespace std;

const int maxlen=10;

bool smaller(char first[], char second[]) {
  int count = 0;
  while (first[count] && second[count]) {
    if (first[count] < second[count])
      return true;
    else
      return false;
    count++;
  }
  if (first[count]='\0' && second[count]!='\0')
    return true;
  else
    return false;
}

int main(){
  char first[maxlen], second[maxlen];

  cout << "Enter first string with no caps, spaces or non-alphanumerics with fewer chars than " << maxlen << endl;
  cin >> first;
  cout << "Enter second string with no caps, spaces or non-alphanumerics with fewer chars than " << maxlen << endl;
  cin >> second;

  if (smaller(first,second))
    cout << first << " is smaller than " << second << endl;
  else
    cout << first << " is not smaller than " << second << endl;

  return 0;
}
