#include<iostream>
#include<cstring>
using namespace std;

void rmrep(char a[]){
  for(int i=strlen(a)-1; i>0; i--){
    if(yesrep(a[i],a,i))
    rm(a,i);
  }
}

bool yesrep(char character, char a[], int stop){
  for (int i=0;i<stop;i++){
    if(a[i]==character)
    return true;
  }
  return false;
}

void rm(char a[], int start){
  int i=start;
  while(a[i]!='\0'){
    a[i]=a[i+1];
    i++;
  }
}

int main(){
  char str[90];
  cout << "Type in a string: ";
  cin.getline(str,90);
  rmrep(str);
  cout << "The string without repetition is: " << str << endl;

  return 0;
}
