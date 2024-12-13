#include "warehousemanager.h"
dimkashelk::WarehouseManager::WarehouseManager(std::vector < Robot > robots):
  robots_(std::move(robots))
{
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
  if (!available_robots())
  {
    throw std::runtime_error("No available robots to handle the order");
  }
  for (auto &robot: robots_)
  {
    if (robot.available())
    {
      robot.set_order(order);
      robot.start_order();
      current_order_ = order;
      break;
    }
  }
}
void dimkashelk::WarehouseManager::set_status(Order &order, ExecutionStatus status)
{
  std::lock_guard lock(mutex_);
  order.set_status(status);
}
