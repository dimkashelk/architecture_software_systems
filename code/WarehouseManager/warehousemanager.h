#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H
#include <vector>
#include <OrderStack/orderstack.h>
#include <Robot/robot.h>

namespace dimkashelk
{
  class WarehouseManager
  {
  public:
    WarehouseManager(std::vector < Robot > &robots, OrderStack &order_stack);
    bool available_robots();
    void add_order(const Order &order);
    void set_status(Order &order, ExecutionStatus status);
    ~WarehouseManager();

  private:
    void process_orders();

    void assign_order_to_robot(const Order &order)
    {
      // Циклическое назначение робота
      for (size_t i = 0; i < robots_.size(); ++i)
      {
        size_t index = (current_robot_index_ + i) % robots_.size();
        if (robots_[index].available())
        {
          robots_[index].set_order(order);
          robots_[index].start_order();
          current_robot_index_ = (index + 1) % robots_.size();
          return;
        }
      }

      // Если нет доступных роботов, заказ не назначается (опционально можно обработать ошибку)
    }
    std::vector < Robot > robots_;
    OrderStack &order_stack_;
    std::thread worker_thread_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic < bool > stop_flag_;
    size_t current_robot_index_;
  };
}
#endif
