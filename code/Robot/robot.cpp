#include "robot.h"
#include <thread>
#include <chrono>
#include <Order/execution_status.h>
void dimkashelk::Robot::set_order(const Order &order)
{
  std::lock_guard lock(mtx_);
  if (work_now_)
  {
    throw std::runtime_error("Robot is busy and cannot accept a new order.");
  }
  current_order_ = order;
}
void dimkashelk::Robot::start_order()
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
bool dimkashelk::Robot::available() const
{
  std::lock_guard lock(mtx_);
  return !work_now_;
}
void dimkashelk::Robot::finish_order()
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
void dimkashelk::Robot::run()
{
  const size_t wait_time = calculate_wait_time();
  std::this_thread::sleep_for(std::chrono::seconds(wait_time));
  finish_order();
}
size_t dimkashelk::Robot::calculate_wait_time() const
{
  if (!current_order_.has_value())
  {
    throw std::runtime_error("No order assigned to calculate wait time.");
  }
  const size_t to = current_order_->get_to();
  const size_t from = current_order_->get_from();
  if (to > from)
  {
    return to - from;
  }
  else
  {
    return from - to;
  }
}
