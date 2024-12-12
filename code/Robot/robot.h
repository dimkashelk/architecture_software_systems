#ifndef ROBOT_H
#define ROBOT_H
#include <optional>
#include <mutex>
#include <Order/order.h>

namespace dimkashelk
{
  class Robot
  {
  public:
    void set_order(const Order &order);
    void start_order();
    bool available() const;

  private:
    void finish_order();
    void run();
    size_t calculate_wait_time() const;
    std::optional < Order > current_order_;
    bool work_now_ = false;
    mutable std::mutex mtx_;
  };
}
#endif
