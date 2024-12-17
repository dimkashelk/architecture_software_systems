#include <gtest/gtest.h>
#include <thread>
#include <robot.h>
#include <order.h>
TEST(RobotTest, SetOrderSuccessfully)
{
  dimkashelk::Robot robot(0);
  const dimkashelk::Order order(1, 5);
  ASSERT_NO_THROW(robot.set_order(std::make_shared<dimkashelk::Order>(order)));
  EXPECT_TRUE(robot.available());
}
TEST(RobotTest, StartOrderSuccessfully)
{
  dimkashelk::Robot robot(0);
  const dimkashelk::Order order(2, 7);
  robot.set_order(std::make_shared<dimkashelk::Order>(order));
  ASSERT_NO_THROW(robot.start_order());
  EXPECT_FALSE(robot.available());
}
TEST(RobotTest, FinishOrderSuccessfully)
{
  dimkashelk::Robot robot(0);
  constexpr size_t from = 3;
  constexpr size_t to = 5;
  const dimkashelk::Order order(from, to);
  robot.set_order(std::make_shared<dimkashelk::Order>(order));
  robot.start_order();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  EXPECT_TRUE(robot.available());
}
TEST(RobotTest, CannotSetOrderWhenBusy)
{
  dimkashelk::Robot robot(0);
  dimkashelk::Order order1(4, 9);
  dimkashelk::Order order2(5, 10);
  robot.set_order(std::make_shared<dimkashelk::Order>(order1));
  robot.start_order();
  EXPECT_THROW(robot.set_order(std::make_shared<dimkashelk::Order>(order2)), std::runtime_error);
}
TEST(RobotTest, ThrowsWhenStartingWithoutOrder)
{
  dimkashelk::Robot robot(0);
  EXPECT_THROW(robot.start_order(), std::logic_error);
}
TEST(RobotTest, ThrowsWhenCalculatingWaitWithoutOrder)
{
  dimkashelk::Robot robot(0);
  EXPECT_THROW(robot.start_order(), std::logic_error);
}
TEST(RobotTest, MultiThreadedExecution)
{
  dimkashelk::Robot robot(0);
  constexpr size_t from_1 = 3;
  constexpr size_t to_1 = 5;
  constexpr size_t from_2 = 1;
  constexpr size_t to_2 = 2;
  const dimkashelk::Order order1(from_1, to_1);
  const dimkashelk::Order order2(from_2, to_2);
  robot.set_order(std::make_shared<dimkashelk::Order>(order1));
  robot.start_order();
  std::this_thread::sleep_for(std::chrono::seconds(to_1 - from_1 + 1));
  EXPECT_TRUE(robot.available());
  robot.set_order(std::make_shared<dimkashelk::Order>(order2));
  robot.start_order();
  std::this_thread::sleep_for(std::chrono::seconds(to_2 - from_2 + 1));
  EXPECT_TRUE(robot.available());
}
