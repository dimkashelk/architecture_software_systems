#include <Client/client.h>
#include <gtest/gtest.h>
#include "code/mockordermanager.h"
TEST(ClientTest, GeneratesOrders)
{
  dimkashelk::MockOrderManager order_manager(3);
  dimkashelk::Client client(order_manager);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  const auto &orders = order_manager.get_received_orders();
  ASSERT_GE(orders.size(), 2) << "At least two orders are expected";
  std::set < uint > ids;
  for (const auto &order: orders)
  {
    ids.insert(order.get_id());
  }
  ASSERT_EQ(orders.size(), ids.size()) << "The order IDs must be unique";
}
TEST(ClientTest, StopsGracefully)
{
  dimkashelk::MockOrderManager order_manager(3);
  {
    dimkashelk::Client client(order_manager);

    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  SUCCEED() << "Client должен корректно завершить свой поток при уничтожении";
}
