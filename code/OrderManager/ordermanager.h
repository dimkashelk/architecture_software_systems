#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include <mutex>
#include <thread>
#include <Order/order.h>
#include <OrderStack/orderstack.h>

namespace dimkashelk
{
  class OrderManager
  {
  public:
    explicit OrderManager(size_t size_order);
    void add_order(const Order &order);
    void failed_order(Order &order) const;
    void done_order(Order &order) const;

  private:
    OrderStack order_stack_;
    OrderManager &order_manager_;
    std::thread worker_thread_;
    std::atomic<bool> stop_flag_;
    mutable std::mutex mtx_;
  };
}
#endif
