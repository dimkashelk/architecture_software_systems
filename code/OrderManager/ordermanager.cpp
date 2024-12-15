#include "ordermanager.h"
#include <eventmanager.h>
dimkashelk::OrderManager::OrderManager(const size_t size_order):
  order_stack_(std::make_shared < OrderStack >(size_order))
{
  EventManager::getInstance().logEvent("(OrderManager) constructor called");
}
void dimkashelk::OrderManager::add_order(const std::shared_ptr < Order > &order) const
{
  std::lock_guard lock(mtx_);
  order_stack_->add_order(order);
  EventManager::getInstance().logEvent("(OrderManager) add order " + order->to_string() + " to order stack");
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
  return order_stack_->get_length();
}
