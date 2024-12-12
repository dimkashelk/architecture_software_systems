#ifndef ROBOT_H
#define ROBOT_H
#include <optional>
#include <mutex>
#include <thread>
#include <chrono>
#include <Order/order.h>
#include <Order/execution_status.h>

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
    int calculate_wait_time() const;
    std::optional < Order > current_order_;
    bool work_now_ = false;
    mutable std::mutex mtx_;
  };
}
#endif
