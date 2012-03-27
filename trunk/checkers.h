#include <iostream>
#include <vector>

using namespace std;

class checkers {
 public:
  checkers();
  ~checkers();
  void print();
  void play();

 private:
  vector <vector <int> > board;
};
