#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include <memory>
#include <mutex>
#include <Order/order.h>
#include <OrderStack/orderstack.h>
#include <WarehouseManager/warehousemanager.h>

namespace dimkashelk
{
  class WarehouseManager;
  class OrderManager
  {
    friend class WarehouseManager;

  public:
    explicit OrderManager(size_t size_order);
    void add_order(const std::shared_ptr < Order > &order) const;
    void failed_order(Order &order) const;
    void done_order(Order &order) const;
    size_t count_orders() const;

  private:
    std::shared_ptr < OrderStack > order_stack_;
    mutable std::mutex mtx_;
  };
}
#endif
