#include "robot.h"
#include <chrono>
#include <cmath>
#include <eventmanager.h>
#include <execution_status.h>
dimkashelk::Robot::Robot(const size_t id):
  id_(id),
  wait_time_coeff_(0.0),
  start_time_(std::chrono::high_resolution_clock::now()),
  work_time_(0),
  work_now_(false),
  stop_flag_(false),
  gen_(rd_()),
  dis_(0.0, 1.0)
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
      EventManager::getInstance().logEvent(
        "(Robot) " + to_string() + " already work with " + current_order_->get()->to_string());
      throw std::runtime_error("Robot is busy and cannot accept a new order.");
    }
    if (!current_order_.has_value())
    {
      EventManager::getInstance().logEvent("(Robot) no order in " + to_string());
      throw std::logic_error("No order assigned to the robot.");
    }
    work_now_ = true;
    EventManager::getInstance().logEvent(
      "(Robot) " + to_string() + " start work with " + current_order_->get()->to_string());
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
  return !work_now_;
}
double dimkashelk::Robot::get_usage_percent() const
{
  const auto current_time = std::chrono::high_resolution_clock::now();
  const auto diff = std::chrono::duration_cast < std::chrono::microseconds >(current_time - start_time_).count();
  if (diff == 0)
  {
    return 0;
  }
  return static_cast < double >(work_time_) / static_cast < double >(diff);
}
void dimkashelk::Robot::success_order()
{
  std::unique_lock lock(mtx_);
  if (!work_now_ || !current_order_.has_value())
  {
    EventManager::getInstance().logEvent("(Robot) " + to_string() + " can't finish order, no order");
    throw std::runtime_error("Cannot finish an order. Robot is not working.");
  }
  EventManager::getInstance().logEvent("(Robot) " + to_string() + " finished order " +
                                       current_order_->get()->to_string());
  current_order_->get()->set_status(EXECUTION_DONE);
  finish_order();
}
void dimkashelk::Robot::failed_order()
{
  std::unique_lock lock(mtx_);
  if (!work_now_ || !current_order_.has_value())
  {
    EventManager::getInstance().logEvent("(Robot) " + to_string() + " can't finish order, no order");
    throw std::runtime_error("Cannot finish an order. Robot is not working.");
  }
  EventManager::getInstance().logEvent("(Robot) " + to_string() + " failed order " +
                                       current_order_->get()->to_string());
  current_order_->get()->set_status(EXECUTION_FAILED);
  finish_order();
}
void dimkashelk::Robot::finish_order()
{
  work_now_ = false;
  current_order_.reset();
  cv_.notify_all();
}
void dimkashelk::Robot::run()
{
  const auto start_run_time = std::chrono::high_resolution_clock::now();
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
  if (dis_(gen_) < 0.05)
  {
    failed_order();
  }
  else
  {
    success_order();
  }
  const auto end_run_time = std::chrono::high_resolution_clock::now();
  work_time_ += std::chrono::duration_cast < std::chrono::microseconds >(end_run_time - start_run_time).count();
}
size_t dimkashelk::Robot::calculate_wait_time()
{
  const auto wait_time = static_cast < size_t >(std::exp(wait_time_coeff_));
  wait_time_coeff_ += 0.1;
  return wait_time;
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
