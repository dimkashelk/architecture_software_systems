#include "warehousemanager.h"
#include <eventmanager.h>
dimkashelk::WarehouseManager::WarehouseManager(const size_t count_robots, const OrderManager &order_manager):
  robots_(count_robots),
  order_stack_(order_manager.order_stack_),
  stop_flag_(false),
  current_robot_index_(0)
{
  EventManager::getInstance().logEvent("(WarehouseManager) constructor called");
  worker_thread_ = std::thread(&WarehouseManager::process_orders, this);
  for (size_t i = 0; i < robots_.size(); ++i)
  {
    robots_[i] = std::make_shared < Robot >(i);
    EventManager::getInstance().logEvent("(WarehouseManager) added " + robots_[i]->to_string() +
                                         " in position " + std::to_string(i));
  }
}
bool dimkashelk::WarehouseManager::available_robots()
{
  std::lock_guard lock(mutex_);
  return std::any_of(robots_.begin(), robots_.end(), [](const std::shared_ptr < Robot > &robot)
  {
    return robot->available();
  });
}
void dimkashelk::WarehouseManager::add_order(const std::shared_ptr < Order > &order)
{
  std::lock_guard lock(mutex_);
  EventManager::getInstance().logEvent("(WarehouseManager) added " + order->to_string());
  order_stack_->add_order(order);
  cv_.notify_one();
}
void dimkashelk::WarehouseManager::set_status(Order &order, const ExecutionStatus status)
{
  EventManager::getInstance().logEvent("(WarehouseManager) set_status to " + order.to_string() + " status:" +
                                       executionStatusToString(status));
  order.set_status(status);
}
void dimkashelk::WarehouseManager::add_robot()
{
  std::lock_guard lock(mutex_);
  robots_.push_back(std::make_shared < Robot >(robots_.size() + 1));
  EventManager::getInstance().logEvent("(WarehouseManager) add new " + robots_.back()->to_string());
}
void dimkashelk::WarehouseManager::pop_back_robot()
{
  std::lock_guard lock(mutex_);
  EventManager::getInstance().logEvent("(WarehouseManager) remove last " + robots_.back()->to_string());
  robots_.pop_back();
}
dimkashelk::WarehouseManager::~WarehouseManager()
{
  {
    std::lock_guard lock(mutex_);
    stop_flag_ = true;
  }
  cv_.notify_all();
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
}
void dimkashelk::WarehouseManager::process_orders()
{
  EventManager::getInstance().logEvent("(WarehouseManager) processing orders");
  while (true)
  {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [this]
    {
      return stop_flag_ || order_stack_->get_length() > 0;
    });
    if (stop_flag_)
    {
      break;
    }
    if (order_stack_->get_length() > 0)
    {
      EventManager::getInstance().logEvent("(WarehouseManager) find order");
      auto order = order_stack_->get_first();
      order_stack_->remove_first();
      assign_order_to_robot(order);
    }
    else
    {
      EventManager::getInstance().logEvent("(WarehouseManager) no order found");
    }
  }
}
void dimkashelk::WarehouseManager::assign_order_to_robot(const std::shared_ptr < Order > &order)
{
  for (size_t i = 0; i < robots_.size(); ++i)
  {
    if (const size_t index = (current_robot_index_ + i) % robots_.size(); robots_[index]->available())
    {
      EventManager::getInstance().logEvent("(WarehouseManager) set " + order->to_string() +
                                           " to robot " + robots_[index]->to_string());
      robots_[index]->set_order(order);
      robots_[index]->start_order();
      current_robot_index_ = (index + 1) % robots_.size();
      return;
    }
  }
}
