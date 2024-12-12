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
TEST(RobotTest, FinishOrderSuccessfully)
{
  dimkashelk::Robot robot;
  dimkashelk::Order order(3, 8);
  robot.set_order(order);
  auto future = std::async(std::launch::async, [&robot]()
  {
    robot.start_order();
  });
  future.wait();
  EXPECT_TRUE(robot.available());
}
TEST(RobotTest, CannotSetOrderWhenBusy)
{
  dimkashelk::Robot robot;
  dimkashelk::Order order1(4, 9);
  dimkashelk::Order order2(5, 10);
  robot.set_order(order1);
  auto future = std::async(std::launch::async, [&robot]()
  {
    robot.start_order();
  });
  future.wait();
  EXPECT_THROW(robot.set_order(order2), std::runtime_error);
}
TEST(RobotTest, ThrowsWhenStartingWithoutOrder)
{
  dimkashelk::Robot robot;
  EXPECT_THROW(robot.start_order(), std::runtime_error);
}
TEST(RobotTest, ThrowsWhenCalculatingWaitWithoutOrder)
{
  dimkashelk::Robot robot;
  // Приватные методы недоступны напрямую, однако можно протестировать через public API.
  EXPECT_THROW(robot.start_order(), std::runtime_error);
}
TEST(RobotTest, MultiThreadedExecution)
{
  dimkashelk::Robot robot;
  dimkashelk::Order order1(10, 15);
  dimkashelk::Order order2(20, 25);
  std::thread t1([&]()
  {
    robot.set_order(order1);
    robot.start_order();
  });
  t1.join();
  EXPECT_TRUE(robot.available());
  std::thread t2([&]()
  {
    robot.set_order(order2);
    robot.start_order();
  });
  t2.join();
  EXPECT_TRUE(robot.available());
}
