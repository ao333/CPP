// must be compiled with -std=c++11 so list iterator works correctly

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class User;

class Authorisation;

class Workstation {
private:
  string hostname;
  list<Authorisation *> authorisations;
public:
  Workstation(string h) : hostname(h) {
  }
  void add_authorisation(Authorisation *auth) {
    authorisations.push_back(auth);
  }
  Authorisation *get_authorisation(User *target);
  string get_hostname() const { return hostname; }
};

class User {
private:
  string name;
public:
  User(string n) : name(n) {
  }
  bool login(Workstation &w) {
    Authorisation *auth = w.get_authorisation(this);
    cout << "login of user '" << name << "' into " << w.get_hostname() << " ";
    if (auth == NULL) {
      cout << "failed due to lack of authorisation." << endl;
      return false;
    }
    cout << "succeeded!"<< endl;
    return true;
  }
};

class StartSession {
private:
  string root;
public:
  StartSession(string r) : root(r) {
  }
  // copy constructor
  StartSession(const StartSession &other) : root(other.root) {
  }
  
};

class Directory {
private:
  string name;
  Directory *parent;
public:
  Directory(string _name, Directory *p) : name(_name), parent(p) {
  }
};

class Authorisation {
private:
  int priority;
  User *user;
  Workstation *workstation;
  StartSession start;
  Directory *default_directory;
public:
  Authorisation(User *u, Workstation *w, int p, const StartSession &s, Directory *def) : priority(p), user(u), workstation(w), start(s), default_directory(def) {
    w->add_authorisation(this);
  }
  bool matches_user(User *target) {
    return user == target;
  }
};
 
Authorisation *Workstation::get_authorisation(User *target) {
    // go through list looking for target user
    // note lazy use of auto to get type for iterator
    for (auto iterator = authorisations.begin(); iterator != authorisations.end(); iterator++) {
      if ((*iterator)->matches_user(target)) 
        return *iterator;
    }
    return NULL;
}
 
int main() {
  User will("will");
  Workstation beast("beast");
  Workstation mi5("topsecret");

  StartSession sess("/bin/sh");
  Directory root("/", NULL);
  Directory homes("/homes",&root);
  Directory def("/homes/wjk",&homes);

  Authorisation auth(&will, &beast, 10, sess, &def);

  will.login(mi5);
  will.login(beast);
  
  return 0;
}
