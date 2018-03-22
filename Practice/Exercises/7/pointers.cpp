#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int maxlen = 1000;

struct Node {
  char word[maxlen];
  Node* next;
};
typedef Node* node_ptr;

void new_node(node_ptr &a_node){
  a_node = new Node;

  if (a_node == NULL){
    cout << "sorry - no more memory\n";
    exit(1);
  }
}

void create_list(node_ptr &head){
  node_ptr current_node, last_node;

  new_node(head);
  cout << "Enter first word (or '.' to end list): ";
  cin >> head->word;
  if (!strcmp(".",head->word)){
    delete head;
    head = NULL;
  }
  current_node = head;

  while (current_node != NULL){
    new_node(last_node);
    cout << "Enter next word (or '.' to end list): ";
    cin >> last_node->word;
    if (!strcmp(".",last_node->word)){
      delete last_node;
      last_node = NULL;
    }
    current_node->next = last_node;
    current_node = last_node;
  }
}

void print(node_ptr a_node) {
  while (a_node != NULL){
    cout << a_node->word << " ";
    a_node = a_node->next;
  }
}

void add_after(node_ptr &a_list, char word[], char word_after[]){
  node_ptr current_node = a_list, extra_node;

  new_node(extra_node);
  strcpy(extra_node->word, word_after);

  while (current_node != NULL) {
    if (!strcmp(word, current_node->word)) {
      extra_node->next = current_node->next;
      current_node->next = extra_node;
      return;
    }
    current_node = current_node->next;
  }
  delete extra_node;
}

void delete_node(node_ptr &head, char word[]) {
  node_ptr node_before = head, node_deleted = head;

  while (node_deleted != NULL){
    if(!strcmp(word, node_deleted->word)){
      if(node_deleted == head)
        head = node_deleted->next;
      else
        node_before->next = node_deleted->next;
      delete node_deleted;
      return;
    }
    node_before = node_deleted;
    node_deleted = node_deleted->next;
  }
}

bool smaller(char a[], char b[]){
  int count = 0;

  while (a[count] != '\0' && b[count] != '\0'){
    if (a[count] < b[count])
      return true;
    if (a[count] > b[count])
      return false;
      count++;
  }
  if (a[count] == '\0' && b[count] != '\0')
    return true;
  else
    return false;
}

void list_selection_sort(node_ptr &head){
  node_ptr current_node = head, smallest_node = head;
  char temp[maxlen];

  while (current_node != NULL){
    if (smaller(current_node->word, smallest_node->word))
      smallest_node = current_node;
    current_node = current_node->next;

    strcpy(temp, current_node->word);
    strcpy(current_node->word, smallest_node->word);
    strcpy(smallest_node->word,temp);

    current_node = current_node->next;
  }
}

int main() {
  node_ptr list = NULL;
  char word[maxlen];
  char word_after[maxlen];

  create_list(list);

  cout << "\nTHE LIST IS NOW:\n";
  print(list);

  cout << "\n\nAFTER WHICH WORD WOULD YOU LIKE TO ADD AN EXTRA WORD? ";
  cin >> word;
  cout << "WHICH WORD WOULD YOU LIKE TO ADD? ";
  cin >> word_after;
  add_after(list, word, word_after);
  cout << "\nThe LIST IS NOW:\n";
  print(list);

  cout << "\n\nWHICH WORD WOULD YOU LIKE TO DELETE? ";
  cin >> word;
  delete_node(list,word);
  cout << "\nTHE LIST IS NOW:\n";
  print(list);

  list_selection_sort(list);
  cout << "\n\nAFTER SORTING, THE LIST IS:\n";
  print(list);
  cout << endl;

  return 0;
}
