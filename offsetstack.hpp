#ifndef OFFSETSTACK_H
#define OFFSETSTACK_H

#include <vector>

using std::vector;

class OffsetStack {
  vector<int> stack;

 public:
  void duplicateLastItem();
  void increaseOffset();
  void decreaseOffset();
};

#endif