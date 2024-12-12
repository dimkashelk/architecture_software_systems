#include <gtest/gtest.h>
#include <Order/order.h>
#include <thread>
#include <future>
#include <Robot/robot.h>
TEST(RobotTest, SetOrderSuccessfully)
{
  dimkashelk::Robot robot;
  const dimkashelk::Order order(1, 5);
  ASSERT_NO_THROW(robot.set_order(order));
  EXPECT_TRUE(robot.available() == false);
}
TEST(RobotTest, StartOrderSuccessfully)
{
  dimkashelk::Robot robot;
  const dimkashelk::Order order(2, 7);
  robot.set_order(order);
  ASSERT_NO_THROW(robot.start_order());
  EXPECT_FALSE(robot.available());
}
