#include<iostream>
using namespace std;

const int maxlen=100;

void string_sort(char unsorted[]){
  int count = 0;
  while (unsorted[count] != '\0'){
    swap(unsorted[count],unsorted[min(unsorted,count)]);
    count++;
  }
}

int min(char unsorted[], int pos){
  int min_index = pos;
  int count = pos + 1;

  while (unsorted[count] != '\0'){
    if (unsorted[count] < unsorted[min_index])
    min_index = count;
    count++;
  }
  return min_index;
}

void swap(char& first, char& second){
  char temp = first;
  first = second;
  second = temp;
}

int main(){
  char str[maxlen];

  cout << "Type in unsorted string: ";
  cin.getline(str,maxlen);
  string_sort(str);
  cout << "The sorted string is:  " << str << endl;

  return 0;
}
