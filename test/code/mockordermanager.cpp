#include "mockordermanager.h"
void dimkashelk::MockOrderManager::add_order(const Order &order)
{
  std::lock_guard lock(mtx_);
  received_orders_.push_back(order);
}
const std::vector < dimkashelk::Order > &dimkashelk::MockOrderManager::get_received_orders() const
{
  return received_orders_;
}
