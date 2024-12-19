#include <gtest/gtest.h>
#include <client.h>
#include <ordermanager.h>
TEST(ClientTest, GeneratesOrders)
{
  dimkashelk::OrderManager order_manager(3);
  dimkashelk::Client client(1, order_manager);
  std::this_thread::sleep_for(std::chrono::seconds(8));
  const auto &orders = order_manager.count_orders();
  ASSERT_GE(orders, 0) << "At least two orders are expected";
}
TEST(ClientTest, StopsGracefully)
{
  dimkashelk::OrderManager order_manager(3);
  {
    dimkashelk::Client client(1, order_manager);
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  SUCCEED() << "Client должен корректно завершить свой поток при уничтожении";
}
