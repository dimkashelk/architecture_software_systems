#include "client.h"
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <vector>
#include <Order/order.h>
#include <OrderManager/ordermanager.h>
dimkashelk::Client::Client(OrderManager &order_manager):
  order_manager_(order_manager),
  stop_flag_(false)
{
  std::srand(static_cast < unsigned >(std::time(nullptr)));
  worker_thread_ = std::thread([this]
  {
    this->run();
  });
}
void dimkashelk::Client::generate_order()
{
  constexpr size_t range = 20;
  const size_t from = std::rand() % range;
  size_t to = std::rand() % range;
  while (to == from)
  {
    to = std::rand() % range;
  }
  Order new_order(from, to);
  {
    std::lock_guard lock(mtx_);
    orders_.emplace_back(new_order);
  }
  order_manager_.add_order(new_order);
}
void dimkashelk::Client::run()
{
  while (!stop_flag_)
  {
    generate_order();
    const size_t time = static_cast < size_t >(std::rand() % 3);
    std::this_thread::sleep_for(std::chrono::seconds(time));
  }
}
const std::vector < dimkashelk::Order > &dimkashelk::Client::get_orders() const
{
  std::lock_guard lock(mtx_);
  return orders_;
}
dimkashelk::Client::~Client()
{
  stop_flag_ = true;
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
}
