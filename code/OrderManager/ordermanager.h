#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include <memory>
#include <mutex>
#include <order.h>
#include <orderstack.h>
#include <warehousemanager.h>

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
    size_t get_stack_capacity() const;
    void decrement_stack() const;
    void increment_stack() const;
    void resize_stack(size_t new_capacity) const;

  private:
    std::shared_ptr < OrderStack > order_stack_;
    mutable std::mutex mtx_;
  };
}
#endif
