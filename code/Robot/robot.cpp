#include "robot.h"
#include <thread>
#include <chrono>
#include <EventManager/eventmanager.h>
#include <Order/execution_status.h>
dimkashelk::Robot::Robot(const size_t id):
  id_(id),
  work_now_(false),
  stop_flag_(false)
{
  EventManager::getInstance().logEvent("(Robot) robot with id=" + std::to_string(id_) + " created");
}
dimkashelk::Robot::~Robot()
{
  {
    std::lock_guard lock(mtx_);
    stop_flag_ = true;
    cv_.notify_all();
  }
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
}
void dimkashelk::Robot::set_order(const std::shared_ptr < Order > &order)
{
  std::lock_guard lock(mtx_);
  if (work_now_)
  {
    EventManager::getInstance().logEvent("(Robot) " + current_order_->get()->to_string() +
                                         " already set in " + to_string());
    throw std::runtime_error("Robot is busy and cannot accept a new order.");
  }
  current_order_ = order;
  EventManager::getInstance().logEvent("(Robot) " + current_order_->get()->to_string() + " set to " + to_string());
}
void dimkashelk::Robot::start_order()
{
  {
    std::lock_guard lock(mtx_);
    if (work_now_)
    {
      EventManager::getInstance().logEvent("(Robot) " + to_string() + " already work with " + current_order_->get()->to_string());
      throw std::runtime_error("Robot is busy and cannot accept a new order.");
    }
    if (!current_order_.has_value())
    {
      EventManager::getInstance().logEvent("(Robot) no order in " + to_string());
      throw std::logic_error("No order assigned to the robot.");
    }
    work_now_ = true;
    EventManager::getInstance().logEvent("(Robot) " + to_string() + " start work with " + current_order_->get()->to_string());
    current_order_->get()->set_status(EXECUTION_RUN);
  }
  if (worker_thread_.joinable())
  {
    worker_thread_.join();
  }
  worker_thread_ = std::thread([this]
  {
    run();
  });
}
bool dimkashelk::Robot::available() const
{
  std::lock_guard lock(mtx_);
  return !work_now_;
}
void dimkashelk::Robot::finish_order()
{
  std::unique_lock lock(mtx_);
  if (!work_now_ || !current_order_.has_value())
  {
    throw std::runtime_error("Cannot finish an order. Robot is not working.");
  }
  current_order_->get()->set_status(EXECUTION_DONE);
  work_now_ = false;
  current_order_.reset();
  cv_.notify_all();
}
void dimkashelk::Robot::run()
{
  const size_t wait_time = calculate_wait_time();
  {
    std::unique_lock lock(mtx_);
    if (cv_.wait_for(lock, std::chrono::seconds(wait_time), [this]
    {
      return stop_flag_.load();
    }))
    {
      return;
    }
  }
  finish_order();
}
size_t dimkashelk::Robot::calculate_wait_time() const
{
  if (!current_order_.has_value())
  {
    throw std::runtime_error("No order assigned to calculate wait time.");
  }
  const size_t to = current_order_->get()->get_to();
  const size_t from = current_order_->get()->get_from();
  if (to > from)
  {
    return to - from;
  }
  else
  {
    return from - to;
  }
}
std::string dimkashelk::Robot::to_string() const
{
  const std::string str = "Robot{id=" + std::to_string(id_) + ", work_now=" + std::to_string(work_now_);
  if (!current_order_.has_value())
  {
    return str + "}";
  }
  return str + ", order=" + current_order_->get()->to_string() + "}";
}
