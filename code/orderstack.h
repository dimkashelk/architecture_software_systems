#ifndef ORDERSTACK_H
#define ORDERSTACK_H
#include <iostream>
#include <vector>
#include "order.h"

namespace dimkashelk
{
  class OrderStack
  {
  public:
    OrderStack() = delete;
    explicit OrderStack(size_t capacity);
    OrderStack(const OrderStack& other) = delete;
    OrderStack(OrderStack&& other) = delete;
    OrderStack& operator=(const OrderStack& other) = delete;
    OrderStack& operator=(OrderStack&& other) = delete;
    ~OrderStack() = default;
    size_t get_length() const
    {
      return count_;
    }
    void add_order(const Order &order)
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
    Order &get_first()
    {
      if (count_ == 0)
      {
        throw std::runtime_error("Stack is empty!");
      }
      const size_t last_index = (start_ + count_ - 1) % capacity_;
      return stack_[last_index];
    }
    void remove_first()
    {
      if (count_ == 0)
      {
        throw std::runtime_error("Stack is empty!");
      }
      --count_;
    }

  private:
    std::vector < Order > stack_;
    size_t capacity_;
    size_t count_;
    size_t start_;
  };
}
#endif
