#include "warehousemanager.h"
dimkashelk::WarehouseManager::WarehouseManager(std::vector < Robot > &robots, OrderStack &order_stack):
  robots_(std::move(robots)),
  order_stack_(order_stack),
  stop_flag_(false),
  current_robot_index_(0)
{
  worker_thread_ = std::thread(&WarehouseManager::process_orders, this);
}
bool dimkashelk::WarehouseManager::available_robots()
{
  std::lock_guard lock(mutex_);
  return std::any_of(robots_.begin(), robots_.end(), [](const Robot &robot)
  {
    return robot.available();
  });
}
void dimkashelk::WarehouseManager::add_order(const Order &order)
{
  std::lock_guard lock(mutex_);
  order_stack_.add_order(order);
  cv_.notify_one();
}
void dimkashelk::WarehouseManager::set_status(Order &order, ExecutionStatus status)
{
  std::lock_guard lock(mutex_);
  order.set_status(status);
}
dimkashelk::WarehouseManager::~WarehouseManager()
{
  {
    std::lock_guard lock(mutex_);
    stop_flag_ = true;
  }
  cv_.notify_all();
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
}
void dimkashelk::WarehouseManager::process_orders()
{
  while (true)
  {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [this]
    {
      return stop_flag_ || order_stack_.get_length() > 0;
    });
    if (stop_flag_)
    {
      break;
    }
    if (order_stack_.get_length() > 0 and available_robots())
    {
      Order order = order_stack_.get_first();
      order_stack_.remove_first();
      assign_order_to_robot(order);
    }
  }
}
void dimkashelk::WarehouseManager::assign_order_to_robot(const Order &order)
{
  for (size_t i = 0; i < robots_.size(); ++i)
  {
    const size_t index = (current_robot_index_ + i) % robots_.size();
    if (robots_[index].available())
    {
      robots_[index].set_order(order);
      robots_[index].start_order();
      current_robot_index_ = (index + 1) % robots_.size();
      return;
    }
  }
}
