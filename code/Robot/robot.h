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
    void start_order()
    {
      {
        std::lock_guard lock(mtx_);
        if (!current_order_.has_value())
        {
          throw std::runtime_error("No order assigned to the robot.");
        }
        work_now_ = true;
        current_order_->set_status(EXECUTION_RUN);
      }
      run();
    }
    bool available() const
    {
      std::lock_guard lock(mtx_);
      return !work_now_;
    }

  private:
    void finish_order()
    {
      std::lock_guard lock(mtx_);
      if (!work_now_ || !current_order_.has_value())
      {
        throw std::runtime_error("Cannot finish an order. Robot is not working.");
      }
      current_order_->set_status(EXECUTION_DONE);
      work_now_ = false;
      current_order_.reset();
    }
    void run()
    {
      const int wait_time = calculate_wait_time();
      std::this_thread::sleep_for(std::chrono::seconds(wait_time));
      finish_order();
    }
    int calculate_wait_time() const
    {
      if (!current_order_.has_value())
      {
        throw std::runtime_error("No order assigned to calculate wait time.");
      }
      return std::abs(static_cast < int >(current_order_->get_to() - current_order_->get_from()));
    }
    std::optional < Order > current_order_;
    bool work_now_ = false;
    mutable std::mutex mtx_;
  };
}
#endif