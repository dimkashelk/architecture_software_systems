#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H
#include <vector>
#include <OrderManager/ordermanager.h>
#include <OrderStack/orderstack.h>
#include <Robot/robot.h>

namespace dimkashelk
{
  class OrderManager;
  class WarehouseManager
  {
    friend class OrderManager;

  public:
    WarehouseManager(size_t count_robots, OrderManager &order_manager);
    bool available_robots();
    void add_order(const Order &order);
    void set_status(Order &order, ExecutionStatus status);
    ~WarehouseManager();

  private:
    void process_orders();
    void assign_order_to_robot(const Order &order);
    std::vector < Robot > robots_;
    std::shared_ptr < OrderStack > order_stack_;
    std::thread worker_thread_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic < bool > stop_flag_;
    size_t current_robot_index_;
  };
}
#endif
