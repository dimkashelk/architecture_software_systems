#include "orderstack.h"
dimkashelk::OrderStack::OrderStack(const size_t capacity):
  stack_(capacity),
  capacity_(capacity),
  count_(0),
  start_(0)
{
  stack_.resize(capacity);
}
size_t dimkashelk::OrderStack::get_length() const
{
  return count_;
}
void dimkashelk::OrderStack::add_order(const Order &order)
{
  const size_t index = (start_ + count_) % capacity_;
  if (count_ == capacity_)
  {
    start_ = (start_ + 1) % capacity_;
  }
  else
  {
    ++count_;
  }
  stack_[index] = order;
}
