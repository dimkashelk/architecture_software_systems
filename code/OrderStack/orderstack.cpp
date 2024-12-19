#include "orderstack.h"
#include <eventmanager.h>
dimkashelk::OrderStack::OrderStack(const size_t capacity):
  stack_(capacity),
  capacity_(capacity),
  count_(0),
  start_(1)
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
    EventManager::getInstance().logEvent("(OrderStack) resize failed: new capacity (" +
                                         std::to_string(new_capacity) + ") equal to "
                                         "old capacity (" + std::to_string(capacity_) + ")");
    return;
  }
  std::lock_guard lock(mtx_);
  std::vector < std::shared_ptr < Order > > new_stack(new_capacity);
  if (new_capacity < capacity_)
  {
    for (size_t i = new_capacity; i < capacity_; ++i)
    {
      stack_[i]->set_status(EXECUTION_REJECTED);
    }
    EventManager::getInstance().logEvent("(OrderStack) resize done: new capacity < "
                                         "old capacity, rejected " + std::to_string(capacity_ - new_capacity) +
                                         " orders");
    std::copy_n(stack_.begin(), new_capacity, new_stack.begin());
  }
  else
  {
    EventManager::getInstance().logEvent("(OrderStack) resize done: new capacity > old capacity");
    std::copy_n(stack_.begin(), capacity_, new_stack.begin());
  }
  std::swap(stack_, new_stack);
}
void dimkashelk::OrderStack::increase_size()
{
  std::lock_guard lock(mtx_);
  const auto capacity_old = capacity_;
  stack_.insert(std::next(stack_.begin(), start_), nullptr);
  capacity_ = stack_.size();
  EventManager::getInstance().logEvent("(OrderStack) increase done ("
                                       + std::to_string(capacity_) + " > " + std::to_string(capacity_old)
                                       + ")");
  ++start_;
}
void dimkashelk::OrderStack::decrease_size()
{
  if (capacity_ == 1)
  {
    return;
  }
  std::lock_guard lock(mtx_);
  const auto capacity_old = capacity_;
  stack_.erase(std::next(stack_.begin(), start_));
  capacity_ = stack_.size();
  EventManager::getInstance().logEvent("(OrderStack) decrease done ("
                                       + std::to_string(capacity_) + " < " + std::to_string(capacity_old)
                                       + ")");
  start_ = start_ % capacity_;
}
void dimkashelk::OrderStack::add_order(const std::shared_ptr < Order > &order)
{
  std::lock_guard lock(mtx_);
  const size_t index = (start_ + count_) % capacity_;
  if (count_ == capacity_)
  {
    start_ = (start_ + 1) % capacity_;
    stack_[index]->set_status(EXECUTION_REJECTED);
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
