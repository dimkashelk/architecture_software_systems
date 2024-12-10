#include "orderstack.h"
dimkashelk::OrderStack::OrderStack(const size_t capacity):
  stack_(capacity),
  capacity_(capacity),
  count_(0),
  start_(0)
{}
size_t dimkashelk::OrderStack::get_length() const
{
  std::lock_guard lock(mtx_);
  return count_;
}
void dimkashelk::OrderStack::add_order(const Order &order)
{
  std::lock_guard lock(mtx_);
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
dimkashelk::Order &dimkashelk::OrderStack::get_first()
{
  std::lock_guard lock(mtx_);
  if (count_ == 0)
  {
    throw std::runtime_error("Stack is empty!");
  }
  const size_t last_index = (start_ + count_ - 1) % capacity_;
  return stack_[last_index];
}
