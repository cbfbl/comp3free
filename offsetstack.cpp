#include "offsetstack.hpp"

void OffsetStack::duplicateLastItem() { stack.push_back(stack.back()); }
void OffsetStack::increaseOffset() { stack.back()++; }
void OffsetStack::decreaseOffset() { stack.back()--; }