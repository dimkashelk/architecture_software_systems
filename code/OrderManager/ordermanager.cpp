#include "ordermanager.h"
dimkashelk::OrderManager::OrderManager(const size_t size_order):
  order_stack_(size_order)
{}
void dimkashelk::OrderManager::add_order(const Order &order)
{
  std::lock_guard lock(mtx_);
  order_stack_.add_order(order);
}
void dimkashelk::OrderManager::failed_order(Order &order) const
{
  std::lock_guard lock(mtx_);
  order.set_status(EXECUTION_FAILED);
}
void dimkashelk::OrderManager::done_order(Order &order) const
{
  std::lock_guard lock(mtx_);
  order.set_status(EXECUTION_DONE);
}
size_t dimkashelk::OrderManager::count_orders() const
{
  return order_stack_.get_length();
}
