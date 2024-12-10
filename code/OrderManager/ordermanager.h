#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include <mutex>
#include <Order/order.h>
#include <OrderStack/orderstack.h>

namespace dimkashelk
{
  class OrderManager
  {
  public:
    OrderManager() = default;
    void add_order(const Order &order);
    void failed_order(Order &order);
    void done_order(Order &order)
    {
      std::lock_guard lock(_mutex);
      _order_stack.set_status(order, EXECUTION_DONE);
      _order_stack.remove_first();
    }

  private:
    OrderStack _order_stack;
    mutable std::mutex _mutex;
  };
}
#endif
