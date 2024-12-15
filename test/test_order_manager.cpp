#include <gtest/gtest.h>
#include <Order/order.h>
#include <OrderManager/ordermanager.h>
#include <Order/execution_status.h>
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
  dimkashelk::Order order(1, 2);
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
  manager.done_order(order);
  EXPECT_EQ(order.get_status(), dimkashelk::EXECUTION_DONE) << "Order done";
}
TEST(OrderManagerTest, ORDER_DONE_ALOT)
{
  const dimkashelk::OrderManager manager(3);
  dimkashelk::Order order1(1, 2);
  manager.add_order(std::make_shared < dimkashelk::Order >(order1));
  dimkashelk::Order order2(3, 6);
  manager.add_order(std::make_shared < dimkashelk::Order >(order2));
  dimkashelk::Order order3(3, 6);
  manager.add_order(std::make_shared < dimkashelk::Order >(order3));
  dimkashelk::Order order4(3, 6);
  manager.add_order(std::make_shared < dimkashelk::Order >(order4));
  manager.done_order(order1);
  manager.done_order(order2);
  manager.done_order(order3);
  manager.done_order(order4);
  EXPECT_EQ(order1.get_status(), dimkashelk::EXECUTION_DONE) << "Order 1 done";
  EXPECT_EQ(order2.get_status(), dimkashelk::EXECUTION_DONE) << "Order 2 done";
  EXPECT_EQ(order3.get_status(), dimkashelk::EXECUTION_DONE) << "Order 3 done";
  EXPECT_EQ(order4.get_status(), dimkashelk::EXECUTION_DONE) << "Order 4 done";
}
