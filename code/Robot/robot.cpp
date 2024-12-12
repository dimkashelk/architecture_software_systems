#include "robot.h"
#include <thread>
#include <chrono>
#include <Order/execution_status.h>
dimkashelk::Robot::Robot() :
  work_now_(false),
  stop_flag_(false)
{}
dimkashelk::Robot::~Robot()
{
  {
    std::lock_guard lock(mtx_);
    stop_flag_ = true;
    cv_.notify_all();
  }
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
}
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
    if (work_now_)
    {
      throw std::runtime_error("Robot is busy and cannot accept a new order.");
    }
    if (!current_order_.has_value())
    {
      throw std::logic_error("No order assigned to the robot.");
    }
    work_now_ = true;
    current_order_->set_status(EXECUTION_RUN);
  }
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
  worker_thread_ = std::thread([this]
  {
    run();
  });
}
bool dimkashelk::Robot::available() const
{
  std::lock_guard lock(mtx_);
  return !work_now_;
}
void dimkashelk::Robot::finish_order()
{
  std::unique_lock lock(mtx_);
  if (!work_now_ || !current_order_.has_value())
  {
    throw std::runtime_error("Cannot finish an order. Robot is not working.");
  }
  current_order_->set_status(EXECUTION_DONE);
  work_now_ = false;
  current_order_.reset();
  cv_.notify_all();
}
void dimkashelk::Robot::run()
{
  const size_t wait_time = calculate_wait_time();
  {
    std::unique_lock lock(mtx_);
    if (cv_.wait_for(lock, std::chrono::seconds(wait_time), [this]
    {
      return stop_flag_.load();
    }))
    {
      return;
    }
  }
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
