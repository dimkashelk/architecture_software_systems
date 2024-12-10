#include "ordermanager.h"
void dimkashelk::OrderManager::add_order(const Order &order)
{
  std::lock_guard lock(_mutex);
  _order_stack.add_order(order);
}
void dimkashelk::OrderManager::failed_order(Order &order)
{
  std::lock_guard lock(_mutex);
  _order_stack.set_status(order, EXECUTION_FAILED);
  _order_stack.remove_first();
}
void dimkashelk::OrderManager::done_order(Order &order)
{
  std::lock_guard lock(_mutex);
  _order_stack.set_status(order, EXECUTION_DONE);
  _order_stack.remove_first();
}
