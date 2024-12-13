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
    bool available_robots();
    void add_order(const Order &order);
    void set_status(Order &order, ExecutionStatus status);

  private:
    std::vector < Robot > robots_;
    std::optional < Order > current_order_;
    std::mutex mutex_;
  };
}
#endif
