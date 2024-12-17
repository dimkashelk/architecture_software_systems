#ifndef ORDERSTACK_H
#define ORDERSTACK_H
#include <memory>
#include <mutex>
#include <vector>
#include <order.h>

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
    size_t get_capacity() const;
    void resize(size_t new_capacity);
    void increase_size();
    void decrease_size();
    void add_order(const std::shared_ptr < Order > &order);
    std::shared_ptr < Order > &get_first();
    void remove_first();

  private:
    std::vector < std::shared_ptr < Order > > stack_;
    size_t capacity_;
    size_t count_;
    size_t start_;
    mutable std::mutex mtx_;
  };
}
#endif
