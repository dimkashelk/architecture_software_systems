#ifndef ORDERSTACK_H
#define ORDERSTACK_H
#include <mutex>
#include <vector>
#include "Order/order.h"

namespace dimkashelk
{
  class OrderStack
  {
  public:
    OrderStack() = delete;
    explicit OrderStack(size_t capacity);
    OrderStack(const OrderStack &other) = delete;
    OrderStack(OrderStack &&other) = delete;
    OrderStack &operator=(const OrderStack &other) = delete;
    OrderStack &operator=(OrderStack &&other) = delete;
    ~OrderStack() = default;
    size_t get_length() const;
    void add_order(const Order &order);
    Order &get_first();
    void remove_first();

  private:
    std::pmr::vector < Order > stack_;
    size_t capacity_;
    size_t count_;
    size_t start_;
    mutable std::mutex mtx_;
  };
}
#endif
