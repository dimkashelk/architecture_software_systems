#include <gtest/gtest.h>
#include <Order/order.h>
#include <Robot/robot.h>
#include <OrderStack/orderstack.h>
#include <thread>
#include <OrderManager/ordermanager.h>
#include <WarehouseManager/warehousemanager.h>
TEST(WarehouseManagerTests, AddOrderIncreasesStackLength)
{
  dimkashelk::Order order(1, 2);
  dimkashelk::OrderManager manager(3);
  dimkashelk::WarehouseManager warehouse_manager(2, manager);
  warehouse_manager_->add_order(order);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(order_stack_->get_length(), 1);
}
TEST(WarehouseManagerTests, AvailableRobots)
{
  EXPECT_TRUE(warehouse_manager_->available_robots());
  for (auto &robot: robots_)
  {
    robot.set_order(dimkashelk::Order(1, 2));
    robot.start_order();
  }
  EXPECT_FALSE(warehouse_manager_->available_robots());
}
TEST(WarehouseManagerTests, ProcessOrdersAssignsToRobots)
{
  dimkashelk::Order order1(1, 2);
  dimkashelk::Order order2(2, 3);
  dimkashelk::Order order3(3, 4);
  warehouse_manager_->add_order(order1);
  warehouse_manager_->add_order(order2);
  warehouse_manager_->add_order(order3);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  for (const auto &robot: robots_)
  {
    EXPECT_FALSE(robot.available());
  }
}
TEST(WarehouseManagerTests, OrdersProcessedCyclically)
{
  dimkashelk::Order order1(1, 2);
  dimkashelk::Order order2(2, 3);
  dimkashelk::Order order3(3, 4);
  dimkashelk::Order order4(4, 5);
  warehouse_manager_->add_order(order1);
  warehouse_manager_->add_order(order2);
  warehouse_manager_->add_order(order3);
  warehouse_manager_->add_order(order4);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  EXPECT_FALSE(robots_[0].available());
  EXPECT_FALSE(robots_[1].available());
  EXPECT_FALSE(robots_[2].available());
  // Wait until at least one robot finishes the order
  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_TRUE(warehouse_manager_->available_robots());
}
