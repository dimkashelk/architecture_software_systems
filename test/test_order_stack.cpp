#include <gtest/gtest.h>
#include <order.h>
#include <OrderStack/orderstack.h>
TEST(OrderStackTest, ADD_1_ORDER)
{
  dimkashelk::OrderStack order_stack(3);
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  EXPECT_EQ(order_stack.get_length(), 1) << "Different length";
}
TEST(OrderStackTest, ADD_4_ORDER)
{
  dimkashelk::OrderStack order_stack(3);
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  EXPECT_EQ(order_stack.get_length(), 3) << "Different length";
}
TEST(OrderStackTest, TAKE_FIRST_1)
{
  dimkashelk::OrderStack order_stack(3);
  const dimkashelk::Order order(1, 2);
  order_stack.add_order(std::make_shared < dimkashelk::Order >(order));
  const auto order_from_stack = order_stack.get_first();
  EXPECT_EQ(order.get_id(), order_from_stack.get()->get_id()) << "Different id";
  order_stack.remove_first();
  EXPECT_EQ(order_stack.get_length(), 0);
}
TEST(OrderStackTest, TAKE_FIRST_2)
{
  dimkashelk::OrderStack order_stack(3);
  for (int i = 0; i < 5; i++)
  {
    order_stack.add_order(std::make_shared < dimkashelk::Order >(1, 2));
  }
  auto order_from_stack = order_stack.get_first();
  EXPECT_EQ(order_from_stack.get()->get_id(), 10) << "Different id: must id of second element in stack";
  order_stack.remove_first();
  EXPECT_EQ(order_stack.get_length(), 2) << "Different length";
  order_from_stack = order_stack.get_first();
  EXPECT_EQ(order_from_stack.get()->get_id(), 9) << "Different id: must id of first element in stack";
  order_stack.remove_first();
  EXPECT_EQ(order_stack.get_length(), 1) << "Different length";
  order_from_stack = order_stack.get_first();
  EXPECT_EQ(order_from_stack.get()->get_id(), 8) << "Different id: must id of second element in stack";
  order_stack.remove_first();
  EXPECT_EQ(order_stack.get_length(), 0) << "Different length";
}
TEST(OrderStackTest, THROW_1)
{
  dimkashelk::OrderStack order_stack(3);
  EXPECT_THROW(order_stack.get_first(), std::runtime_error) << "Wrong throw, stack empty";
}
TEST(OrderStackTest, THROW_2)
{
  dimkashelk::OrderStack order_stack(3);
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  order_stack.remove_first();
  EXPECT_THROW(order_stack.get_first(), std::runtime_error) << "Wrong throw, stack size = 1";
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  order_stack.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 2)));
  order_stack.remove_first();
  order_stack.remove_first();
  EXPECT_THROW(order_stack.get_first(), std::runtime_error) << "Wrong throw, stack size = 2";
}
