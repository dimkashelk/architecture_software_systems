#include <gtest/gtest.h>
#include <Order/order.h>
#include <OrderManager/ordermanager.h>
#include <Order/execution_status.h>
TEST(OrderManagerTest, ADD_ORDER)
{
  dimkashelk::OrderManager manager(3);
  const dimkashelk::Order order(1, 2);
  manager.add_order(order);
}
TEST(OrderManagerTest, ADD_MORE_ORDERS)
{
  dimkashelk::OrderManager manager(3);
  const dimkashelk::Order order(1, 2);
  manager.add_order(order);
  manager.add_order(order);
  manager.add_order(order);
  manager.add_order(order);
  manager.add_order(order);
}
TEST(OrderManagerTest, ORDER_DONE)
{
  dimkashelk::OrderManager manager(3);
  dimkashelk::Order order(1, 2);
  manager.add_order(order);
  manager.done_order(order);
  EXPECT_EQ(order.get_status(), dimkashelk::EXECUTION_DONE) << "Order done";
}
TEST(OrderManagerTest, ORDER_DONE_ALOT)
{
  dimkashelk::OrderManager manager(3);
  dimkashelk::Order order1(1, 2);
  manager.add_order(order1);
  dimkashelk::Order order2(3, 6);
  manager.add_order(order2);
  dimkashelk::Order order3(3, 6);
  manager.add_order(order3);
  dimkashelk::Order order4(3, 6);
  manager.add_order(order4);
  manager.done_order(order1);
  manager.done_order(order2);
  manager.done_order(order3);
  manager.done_order(order4);
  EXPECT_EQ(order1.get_status(), dimkashelk::EXECUTION_DONE) << "Order 1 done";
  EXPECT_EQ(order2.get_status(), dimkashelk::EXECUTION_DONE) << "Order 2 done";
  EXPECT_EQ(order3.get_status(), dimkashelk::EXECUTION_DONE) << "Order 3 done";
  EXPECT_EQ(order4.get_status(), dimkashelk::EXECUTION_DONE) << "Order 4 done";
}
