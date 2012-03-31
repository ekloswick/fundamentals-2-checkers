#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

class checkers {
 public:
  checkers();
  ~checkers();
  void print();
  void play();

 private:
  vector <vector <piece> > board;
};
