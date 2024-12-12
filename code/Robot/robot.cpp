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
