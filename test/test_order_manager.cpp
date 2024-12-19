#include <gtest/gtest.h>
#include <order.h>
#include <ordermanager.h>
#include <execution_status.h>
TEST(OrderManagerTest, ADD_ORDER)
{
  const dimkashelk::OrderManager manager(3);
  const dimkashelk::Order order(1, 2);
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
}
TEST(OrderManagerTest, ADD_MORE_ORDERS)
{
  const dimkashelk::OrderManager manager(3);
  const dimkashelk::Order order(1, 2);
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
}
TEST(OrderManagerTest, ORDER_DONE)
{
  dimkashelk::OrderManager manager(3);
  auto order = std::make_shared < dimkashelk::Order >(1, 2);
  manager.add_order(order);
  order->set_status(dimkashelk::EXECUTION_RUN);
  order->set_status(dimkashelk::EXECUTION_DONE);
  EXPECT_EQ(order->get_status(), dimkashelk::EXECUTION_DONE) << "Order done";
  EXPECT_EQ(manager.count_orders(), 1) << "Count different";
}
