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
    void done_order(Order &order);

  private:
    OrderStack _order_stack;
    mutable std::mutex _mutex;
  };
}
#endif
