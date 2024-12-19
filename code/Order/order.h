#ifndef ORDER_H
#define ORDER_H
#include <chrono>
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
    void set_status(ExecutionStatus status);
    ExecutionStatus get_status() const;
    size_t get_id() const;
    size_t get_from() const;
    size_t get_to() const;
    ~Order() = default;

  private:
    size_t id_;
    size_t from_;
    size_t to_;
    ExecutionStatus status_;
    std::chrono::high_resolution_clock::time_point put_in_stack_time_;
    std::chrono::high_resolution_clock::time_point put_out_stack_time_;
    std::chrono::high_resolution_clock::time_point run_start_time_;
    std::chrono::high_resolution_clock::time_point run_stop_time_;
  };
}
#endif
