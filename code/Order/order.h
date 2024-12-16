#ifndef ORDER_H
#define ORDER_H
#include <cstddef>
#include <string>
#include <execution_status.h>

namespace dimkashelk
{
  class Order
  {
  public:
    Order() = default;
    Order(const Order &other) = default;
    Order(Order &&other) = default;
    Order &operator=(const Order &) = default;
    Order &operator=(Order &&) = default;
    Order(size_t from, size_t to);
    std::string to_string() const;
    void set_status(ExecutionStatus status) noexcept;
    ExecutionStatus get_status() const noexcept;
    size_t get_id() const noexcept;
    size_t get_from() const noexcept;
    size_t get_to() const noexcept;
    ~Order() = default;

  private:
    size_t id_;
    size_t from_;
    size_t to_;
    ExecutionStatus status_;
  };
}
#endif
