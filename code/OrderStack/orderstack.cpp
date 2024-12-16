#include "orderstack.h"
#include <eventmanager.h>
dimkashelk::OrderStack::OrderStack(const size_t capacity):
  stack_(capacity),
  capacity_(capacity),
  count_(0),
  start_(0)
{
  EventManager::getInstance().logEvent("(OrderStack) constructor called");
}
size_t dimkashelk::OrderStack::get_length() const
{
  std::lock_guard lock(mtx_);
  return count_;
}
size_t dimkashelk::OrderStack::get_capacity() const
{
  return capacity_;
}
void dimkashelk::OrderStack::resize(const size_t new_capacity)
{
  if (new_capacity == capacity_)
  {
    return;
  }
  std::lock_guard lock(mtx_);
  std::vector < std::shared_ptr < Order > > new_stack(new_capacity);
  if (new_capacity < capacity_)
  {
    for (size_t i = new_capacity + 1; i < capacity_; ++i)
    {
      stack_[i]->set_status(EXECUTION_REJECTED);
    }
    std::copy_n(stack_.begin(), new_capacity, new_stack.begin());
  }
  else
  {
    std::copy_n(stack_.begin(), capacity_, new_stack.begin());
  }
  std::swap(stack_, new_stack);
}
void dimkashelk::OrderStack::add_order(const std::shared_ptr < Order > &order)
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
  order->set_status(EXECUTION_IN_STACK);
  EventManager::getInstance().logEvent("(OrderStack) add " + order->to_string() +
                                       " in position: " + std::to_string(index));
}
std::shared_ptr < dimkashelk::Order > &dimkashelk::OrderStack::get_first()
{
  std::lock_guard lock(mtx_);
  if (count_ == 0)
  {
    throw std::runtime_error("Stack is empty!");
  }
  const size_t last_index = (start_ + count_ - 1) % capacity_;
  EventManager::getInstance().logEvent("(OrderStack) give away " + stack_[last_index]->to_string() +
                                       " from " + std::to_string(last_index));
  return stack_[last_index];
}
void dimkashelk::OrderStack::remove_first()
{
  std::lock_guard lock(mtx_);
  if (count_ == 0)
  {
    throw std::runtime_error("Stack is empty!");
  }
  const size_t last_index = (start_ + count_ - 1) % capacity_;
  EventManager::getInstance().logEvent("(OrderStack) delete " + stack_[last_index]->to_string() +
                                       " from " + std::to_string(last_index));
  --count_;
}
