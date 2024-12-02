#include <gtest/gtest.h>
#include "../code/order.h"


TEST(OrderTest, IncrementalIdGeneration)
{
  const size_t id1 = dimkashelk::details::Counter::get_obj()->get_id();
  const size_t id2 = dimkashelk::details::Counter::get_obj()->get_id();
  EXPECT_EQ(id2, id1 + 1) << "Second ID should be incremented by 1";

  dimkashelk::Order order1(1, 2);
  dimkashelk::Order order2(3, 4);

  EXPECT_EQ(order1.get_id(), id2 + 1) << "Third ID should be incremented by 1";
  EXPECT_EQ(order2.get_id(), id2 + 2) << "Fourth ID should be incremented by 1";
}
