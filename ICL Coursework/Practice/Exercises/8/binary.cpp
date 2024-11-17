#include<iostream>
using namespace std;

const int MAX = 5;

void quick_sort(int list[],int min,int max){
  int pivot=list[(min+max)/2];
  int left=min;
  int right=max;

  do{
    while(list[right]>pivot)
      right--;
    while(list[left]<pivot)
      left++;
    if(left<=right){
      int temp=list[left];
      list[left]=list[right];
      list[right]=temp;
      left++;
      right--;
    }
  }
  while(right>=left);

  if(min<right)
    quick_sort(list,min,right);
  if(left<max)
    quick_sort(list,left,max);
}

int binary_search(int search_value,int list[],int first,int last){
  if (first>last)
    return -1;
  else{
    int mid=(first+last)/2;
    if(list[mid]==search_value)
      return mid;
    else if (list[mid]>search_value)
      return binary_search(search_value,list,first,mid-1);
    else
      return binary_search(search_value,list,mid+1,last);
  }
}

int main(){
  int list[MAX];
  int count,search_value,position;

  for(count=0; count<MAX; count++) {
    cout << "enter value of element " << count << ": ";
    cin >> list[count];
  }

  cout << "\nbefore quick sort\n";
  for (int count=0; count<MAX; count++)
		cout << list[count] << " ";

  cout << "\nafter quick sort\n";
  quick_sort(list,0,MAX-1);
  for (int count=0; count<MAX; count++)
    cout << list[count] << " ";

  cout << "\nenter the integer you want to search\n";
  cin >> search_value;

  position=binary_search(search_value,list,0,MAX-1);
  if(position==-1)
    cout << "search value cannot be found\n";
  else
    cout << search_value << " is at index " << position << endl;

  return 0;
}
