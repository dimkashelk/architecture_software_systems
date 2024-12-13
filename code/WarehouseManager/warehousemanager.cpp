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
