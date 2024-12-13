#include "client.h"
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <vector>
#include <Order/order.h>
void dimkashelk::Client::generate_order()
{
  std::srand(static_cast < unsigned >(std::time(nullptr)));
  const size_t from = static_cast < size_t >(std::rand() % 100);
  size_t to = static_cast < size_t >(std::rand() % 100);;
  while (to == from)
  {
    to = static_cast < size_t >(std::rand() % 100);
  }
  Order new_order(from, to);
  orders_.emplace_back(new_order);
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
