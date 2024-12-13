#ifndef MOCKORDERMANAGER_H
#define MOCKORDERMANAGER_H
#include <OrderManager/ordermanager.h>

namespace dimkashelk
{
  class MockOrderManager: public OrderManager
  {
  public:
    explicit MockOrderManager(size_t size);
    void add_order(const Order &order);
    const std::vector < Order > &get_received_orders() const;

  private:
    std::vector < Order > received_orders_;
    mutable std::mutex mtx_;
  };
}
#endif
