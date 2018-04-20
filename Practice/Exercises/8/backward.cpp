#include <iostream>
#include <cstring>
using namespace std;

const int maxlen=90;

struct Node{
  char word[maxlen];
  Node* next;
};

void new_list(Node* &list) {
  Node* curr;
  Node* last;
  list = new Node;

  cout << "Enter first word (or '.' to end list); ";
  cin >> list->word;
  if (!strcmp(".", list->word)) {
    delete list;
    list = NULL;
  }
  curr = list;

  while (curr!=NULL) {
    last = new Node;
    cout << "Enter next word (or '.' to end list): ";
    cin >> last->word;
    if (!strcmp(".", last->word)){
      delete last;
      last=NULL;
    }
    curr->next=last;
    curr=last;
  }
}

void print_list_forwards(Node* a_list){
  if(a_list!=NULL){
    cout << a_list->word << " ";
    print_list_forwards(a_list->next);
  }
}

void print_list_backwards(Node* a_list){
  if(a_list!=NULL){
    print_list_backwards(a_list->next);
    cout << a_list->word << " ";
  }
}

int main(){
  Node* a_list = NULL;
  new_list(a_list);

  cout << "\nTHE LIST FORWARDS IS:\n";
  print_list_forwards(a_list);

  cout << "\n\nTHE LIST BACKWARDS IS:\n";
  print_list_backwards(a_list);
  cout << endl;

  return 0;
}
