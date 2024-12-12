#include "robot.h"
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
