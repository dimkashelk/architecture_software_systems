#include <gtest/gtest.h>
#include <thread>
#include <order.h>
#include <robot.h>
#include <orderstack.h>
#include <ordermanager.h>
#include <warehousemanager.h>
TEST(WarehouseManagerTests, AddOrderIncreasesStackLength)
{
  dimkashelk::Order order(1, 2);
  dimkashelk::OrderManager manager(3);
  dimkashelk::WarehouseManager warehouse_manager(2, manager);
  manager.add_order(std::make_shared < dimkashelk::Order >(order));
  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_EQ(manager.count_orders(), 0);
}
TEST(WarehouseManagerTests, AvailableRobots)
{
  dimkashelk::OrderManager manager(3);
  dimkashelk::WarehouseManager warehouse_manager(2, manager);
  EXPECT_TRUE(warehouse_manager.available_robots());
  manager.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 5)));
  manager.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 6)));
  manager.add_order(std::make_shared < dimkashelk::Order >(dimkashelk::Order(1, 7)));
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  EXPECT_FALSE(warehouse_manager.available_robots());
}
