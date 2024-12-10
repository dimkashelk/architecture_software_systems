#include "ordermanager.h"
void dimkashelk::OrderManager::add_order(const Order &order)
{
  std::lock_guard lock(_mutex);
  _order_stack.add_order(order);
}
