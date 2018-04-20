#include <iostream>
#include <string>

using namespace std;

class Item;

class LibraryUser {
private:
  string name;
  int items_borrowed_count;
  Item *items_borrowed[3];
public:
  LibraryUser(string n) : name(n) {
    items_borrowed_count = 0;
    for (int c=0; c<3; c++)
      items_borrowed[c] = NULL;
  }
  bool borrow(Item &target, int days);
};

class Item {
protected:
  int location;
  string title;
  LibraryUser *borrowed_by;
public:
  Item(string t, int l) : title(t), location(l) {
    cout << "Item(" << this << "): constructing with '" << title << "' at location " << location << endl;
    borrowed_by = NULL;
  }
  LibraryUser *get_borrowed_by() const { return borrowed_by; }
  void set_borrowed_by(LibraryUser *person) { borrowed_by = person; }
  virtual int get_loan_period() const=0;
  string get_title() const { return title; }
};

class Book : public Item {
private:
  int loan_period;
public:
  Book(string t, int l, int lp) : Item(t,l), loan_period(lp) {
    cout << "Book(" << this << "): constructing with loan_period = " << loan_period << endl;
  }
  int get_loan_period() const {
    return loan_period;
  }
};

class Periodical : public Item {
private:
  static int loan_period; 
public:
  Periodical(string t, int l) : Item(t,l) {
  }
  int get_loan_period() const {
    return loan_period;
  }
  static void set_loan_period(int lp) {
    loan_period = lp;
  }
};

bool LibraryUser::borrow(Item &target, int days) {
  if (target.get_borrowed_by() != NULL)  {
    cerr << "Sorry, that item is already on loan!" << endl;
    return false;
  }
  if (items_borrowed_count >= 3) {
    cerr << "Sorry, you have too many items already on loan" << endl;
    return false;
  }
  if (days > target.get_loan_period()) {
    cerr << "Sorry, you've asked for too long" << endl;
    return false;
  }
  target.set_borrowed_by(this);

  //  items_borrowed[items_borrowed_count++] = &target;

  bool success = false;
  for (int n=0; n<3; n++) {
    if (items_borrowed[n] == NULL) {
      items_borrowed[n] = &target;
      success = true;
      break;
    }
  }

  if (!success) {
    cerr << "Internal error" << endl;
    return false;
  }

  cout << name << " successfully borrows " << target.get_title() << endl;
  
  items_borrowed_count++;
  return true;
}

int Periodical::loan_period = 5;
  
int main() {

  Book cppwt("C++ Without Tears", 1, 10);
  Book hhgitc("Hitchhikers Guide to IC", 2, 13);

  Item *i = &cppwt;
  cout << i->get_loan_period() << endl;

  Periodical::set_loan_period(7);

  Periodical atwww80("Around...", 3);
  Periodical tmuqt("20m under the Queen's Tower", 4);
  
  LibraryUser ali("ali");
  LibraryUser georgia("georgia");

  georgia.borrow(hhgitc, 7);
  ali.borrow(hhgitc, 7);
  
  return 0;
}
