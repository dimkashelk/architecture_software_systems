#include <gtest/gtest.h>
#include "orderstack.h"
#include "order.h"
TEST(OrderStackTest, ADD_1_ORDER)
{
  dimkashelk::OrderStack order_stack(3);
  order_stack.add_order(dimkashelk::Order(1, 2));
  EXPECT_EQ(order_stack.get_length(), 1) << "Different length";
}
TEST(OrderStackTest, ADD_4_ORDER)
{
  dimkashelk::OrderStack order_stack(3);
  order_stack.add_order(dimkashelk::Order(1, 2));
  order_stack.add_order(dimkashelk::Order(1, 2));
  order_stack.add_order(dimkashelk::Order(1, 2));
  order_stack.add_order(dimkashelk::Order(1, 2));
  EXPECT_EQ(order_stack.get_length(), 3) << "Different length";
}
TEST(OrderStackTest, TAKE_FIRST_OF_1)
{
  dimkashelk::OrderStack order_stack(3);
  dimkashelk::Order order(1, 2);
  order_stack.add_order(order);
  auto order_from_stack = order_stack.get_first();
  EXPECT_EQ(order.get_id(), order_from_stack.get_id()) << "Different id";
  order_stack.remove_first();
  EXPECT_EQ(order_stack.get_length(), 0);
}
