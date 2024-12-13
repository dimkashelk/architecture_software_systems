#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H
#include <vector>
#include <Robot/robot.h>

namespace dimkashelk
{
  class WarehouseManager
  {
  public:
    explicit WarehouseManager(std::vector < Robot > robots);
    bool available_robots()
    {
      std::lock_guard lock(mutex_);
      for (const auto &robot: robots_)
      {
        if (robot.available())
        {
          return true;
        }
      }
      return false;
    }
    void add_order(const Order &order)
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
    void set_status(Order &order, ExecutionStatus status)
    {
      std::lock_guard lock(mutex_);
      order.set_status(status);
    }

  private:
    std::vector < Robot > robots_;
    std::optional < Order > current_order_;
    std::mutex mutex_;
  };
}
#endif
