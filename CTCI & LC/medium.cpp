int binary_search(int list[], int left, int right, int target) {
  int mid_index = (left+right)/2;
  int mid = list[mid_index];
  if (mid == target)
    return mid_index;
  else if (mid>target && mid_index >left)
    return binary_search(list,left,mid_index,target);
  else if(mid<target && mid_index<right)
    return binary_search(list,mid_index+1,right,target);
  else
    return -1;
}

int countPairs(int k, vector<int> a) {
    int count = 0;
    if(a.size()==0) return 0;

    quick_sort(a, 0, static_cast<int>(a.size()-1));
    int left_arrow = 0;
    int right_arrow = static_cast<int>(a.size()-1);
    do {
      while(a[left_arrow]+a[right_arrow]!=k) {
        if(right_arrow == left_arrow)
              break;
        right_arrow--;
      }
      if(right_arrow == left_arrow)
        break;
      if(a[left_arrow]==a[right_arrow]) {
      if(right_arrow-left_arrow ==1)
        count+=1;
      else
        count+=(right_arrow-left_arrow+1)*(right_arrow-left_arrow)/2;
        break;
      }
      count++;
      left_arrow++;
    }
    while (right_arrow != left_arrow);
    return count;
}

long countSteps(int n) {
  long n_1 =1, n_2 =2, n_3 =4, n_4 = 0;
  if (n == 0) return 0;
  if (n == 1) return 1;
  if (n == 2) return 2;
  if (n == 3) return 4;
  for (int index = 4; index <= n; index++) {
    n_4 = n_1 + n_2 + n_3;
    n_1 = n_2;
    n_2 = n_3;
    n_3 = n_4;
  }
  return n_3;
}
