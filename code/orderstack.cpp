#include "orderstack.h"
dimkashelk::OrderStack::OrderStack(const size_t capacity) :
      capacity_(capacity), count_(0), start_(0)
{
  stack_.resize(capacity);
}
