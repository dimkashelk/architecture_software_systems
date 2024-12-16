#include "client.h"
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <vector>
#include <order.h>
#include <ordermanager.h>
dimkashelk::Client::Client(const size_t id, OrderManager &order_manager):
  id_(id),
  stopped_(false),
  order_manager_(order_manager),
  stop_flag_(false)
{
  EventManager::getInstance().logEvent("(Client) Client{id=" + std::to_string(id) + "} created");
  std::srand(static_cast < unsigned >(std::time(nullptr)));
  worker_thread_ = std::thread([this]
  {
    this->run();
  });
}
std::string dimkashelk::Client::to_string() const
{
  return "Client{id=" + std::to_string(id_) + "}";
}
void dimkashelk::Client::start()
{
  stopped_ = false;
  EventManager::getInstance().logEvent("(Client) " + to_string() + " start");
}
void dimkashelk::Client::stop()
{
  stopped_ = true;
  EventManager::getInstance().logEvent("(Client) " + to_string() + " stop");
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
  EventManager::getInstance().logEvent("(Client) " + to_string() + " generated order with id="
                                       + std::to_string(new_order.get_id()));
  const auto shared_new_order = std::make_shared < Order >(new_order);
  {
    std::lock_guard lock(mtx_);
    orders_.push_back(shared_new_order);
  }
  order_manager_.add_order(shared_new_order);
}
void dimkashelk::Client::run()
{
  while (!stop_flag_)
  {
    if (!stopped_)
    {
      generate_order();
    }
    const auto time = static_cast < size_t >(std::rand() % 3);
    std::this_thread::sleep_for(std::chrono::seconds(time));
  }
}
const std::vector < std::shared_ptr < dimkashelk::Order > > &dimkashelk::Client::get_orders() const
{
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
