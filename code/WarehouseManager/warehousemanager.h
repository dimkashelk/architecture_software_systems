#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H
#include <vector>
#include <ordermanager.h>
#include <orderstack.h>
#include <robot.h>

namespace dimkashelk
{
  class OrderManager;
  class WarehouseManager
  {
    friend class OrderManager;

  public:
    WarehouseManager(size_t count_robots, const OrderManager &order_manager);
    bool available_robots();
    void add_order(const std::shared_ptr < Order > &order);
    void set_status(Order &order, ExecutionStatus status);
    ~WarehouseManager();

  private:
    void process_orders();
    void assign_order_to_robot(const std::shared_ptr < Order > &order);
    std::vector < std::shared_ptr < Robot > > robots_;
    std::shared_ptr < OrderStack > order_stack_;
    std::thread worker_thread_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic < bool > stop_flag_;
    size_t current_robot_index_;
  };
}
#endif
