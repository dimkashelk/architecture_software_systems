#include "client.h"
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <vector>
#include <order.h>
#include <ordermanager.h>
dimkashelk::Client::Client(const size_t id, OrderManager &order_manager):
  id_(id),
  delay_(5),
  stopped_(true),
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
size_t dimkashelk::Client::get_orders_count() const
{
  return orders_.size();
}
double dimkashelk::Client::get_failure_rate() const
{
  const auto failed = get_rejected_count();
  const auto orders_count = orders_.size();
  if (orders_count == 0)
  {
    return 0.0;
  }
  return static_cast < double >(failed) / static_cast < double >(orders_count);
}
size_t dimkashelk::Client::get_rejected_count() const
{
  return std::count_if(orders_.begin(), orders_.end(), [](const std::shared_ptr < Order > &order)
  {
    return order->get_status() == EXECUTION_REJECTED;
  });
}
double dimkashelk::Client::get_average_stay_time() const
{
  return get_average_waiting_time() + get_average_execution_time();
}
double dimkashelk::Client::get_average_execution_time() const
{
  long long total_execute_time = 0;
  size_t total_count = 0;
  std::lock_guard lock(mtx_);
  for (const auto &order: orders_)
  {
    const auto order_status = order->get_status();
    if (order_status != EXECUTION_CREATE and order_status != EXECUTION_IN_STACK and order_status != EXECUTION_RUN)
    {
      try
      {
        const auto time = order->get_time_execute();
        if (time >= 0)
        {
          total_execute_time += time;
          total_count++;
        }
      } catch (...)
      {}
    }
  }
  if (total_count == 0)
  {
    return 0.0;
  }
  return static_cast < double >(total_execute_time) / static_cast < double >(total_count);
}
double dimkashelk::Client::get_average_waiting_time() const
{
  long long total_waiting_time = 0;
  size_t total_count = 0;
  std::lock_guard lock(mtx_);
  for (const auto &order: orders_)
  {
    const auto order_status = order->get_status();
    if (order_status != EXECUTION_CREATE and order_status != EXECUTION_IN_STACK)
    {
      try
      {
        const auto time = order->get_time_in_stack();
        if (time >= 0)
        {
          total_waiting_time += time;
          total_count++;
        }
      } catch (...)
      {}
    }
  }
  if (total_count == 0)
  {
    return 0.0;
  }
  return static_cast < double >(total_waiting_time) / static_cast < double >(total_count);
}
double dimkashelk::Client::get_waiting_time_variance() const
{
  const auto average_waiting_time = get_average_waiting_time();
  size_t total = 0;
  double variance = 0;
  for (const auto &order: orders_)
  {
    const auto order_status = order->get_status();
    if (order_status != EXECUTION_CREATE and order_status != EXECUTION_IN_STACK)
    {
      try
      {
        const auto time = order->get_time_in_stack();
        if (time >= 0)
        {
          const auto temp = time - average_waiting_time;
          variance += temp * temp;
          total++;
        }
      } catch (...)
      {}
    }
  }
  if (total == 0)
  {
    return 0.0;
  }
  return variance / static_cast < double >(total);
}
double dimkashelk::Client::get_execution_time_variance() const
{
  const auto average_execution_time = get_average_execution_time();
  size_t total = 0;
  double variance = 0;
  for (const auto &order: orders_)
  {
    const auto order_status = order->get_status();
    if (order_status != EXECUTION_CREATE and order_status != EXECUTION_IN_STACK)
    {
      try
      {
        const auto time = order->get_time_execute();
        if (time >= 0)
        {
          const auto temp = time - average_execution_time;
          variance += temp * temp;
          total++;
        }
      } catch (...)
      {}
    }
  }
  if (total == 0)
  {
    return 0.0;
  }
  return variance / static_cast < double >(total);
}
void dimkashelk::Client::set_delay(const size_t new_delay)
{
  std::lock_guard lock(mtx_);
  delay_ = new_delay;
  EventManager::getInstance().logEvent("(Client) " + to_string() + " set delay "
                                       + std::to_string(delay_) + " seconds");
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
    std::this_thread::sleep_for(std::chrono::seconds(delay_));
  }
}
dimkashelk::Client::~Client()
{
  stop_flag_ = true;
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
}
