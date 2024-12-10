#include "ordermanager.h"
dimkashelk::OrderManager::OrderManager(const size_t size_order):
  order_stack_(size_order)
{}
void dimkashelk::OrderManager::add_order(const Order &order)
{
  std::lock_guard lock(mtx_);
  order_stack_.add_order(order);
}
void dimkashelk::OrderManager::failed_order(Order &order)
{
  std::lock_guard lock(mtx_);
  order_stack_.set_status(order, EXECUTION_FAILED);
  order_stack_.remove_first();
}
void dimkashelk::OrderManager::done_order(Order &order)
{
  std::lock_guard lock(mtx_);
  order_stack_.set_status(order, EXECUTION_DONE);
  order_stack_.remove_first();
}
