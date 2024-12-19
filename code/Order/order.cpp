#include "order.h"
#include <eventmanager.h>
#include <counter.h>
dimkashelk::Order::Order(const size_t from, const size_t to):
  id_(details::Counter::get_obj()->get_id()),
  from_(from),
  to_(to),
  status_(EXECUTION_CREATE)
{
  EventManager::getInstance().logEvent("(Order) create order with id=" + std::to_string(id_) +
                                       ", from=" + std::to_string(from_) + ", to=" +
                                       std::to_string(to_));
  actions_[EXECUTION_CREATE][EXECUTION_IN_STACK] = &Order::set_put_in;
  actions_[EXECUTION_IN_STACK][EXECUTION_RUN] = &Order::set_put_out;
  actions_[EXECUTION_IN_STACK][EXECUTION_REJECTED] = &Order::set_put_out;
  actions_[EXECUTION_RUN][EXECUTION_DONE] = &Order::set_run_stop;
  actions_[EXECUTION_RUN][EXECUTION_FAILED] = &Order::set_run_stop;
}
std::string dimkashelk::Order::to_string() const
{
  return "Order{id=" + std::to_string(id_) + ", from=" + std::to_string(from_) + ", to=" + std::to_string(to_) +
         ", status=" + executionStatusToString(status_) + "}";
}
void dimkashelk::Order::set_status(const ExecutionStatus status)
{
  EventManager::getInstance().logEvent("(Order) Update status of " + to_string() +
                                       " to status: " + executionStatusToString(status));
  actions_[status_][status](*this);
  status_ = status;
}
dimkashelk::ExecutionStatus dimkashelk::Order::get_status() const
{
  return status_;
}
size_t dimkashelk::Order::get_id() const
{
  return id_;
}
size_t dimkashelk::Order::get_from() const
{
  return from_;
}
size_t dimkashelk::Order::get_to() const
{
  return to_;
}
long dimkashelk::Order::get_time_in_stack() const
{
  if (status_ == EXECUTION_IN_STACK or status_ == EXECUTION_CREATE)
  {
    throw std::invalid_argument("Order::get_time_in_stack: invalid status");
  }
  return (put_out_stack_time_ - put_in_stack_time_).count();
}
long dimkashelk::Order::get_time_execute() const
{
  if (status_ == EXECUTION_IN_STACK or status_ == EXECUTION_CREATE or status_ == EXECUTION_RUN)
  {
    throw std::invalid_argument("Order::get_time_execute: invalid status");
  }
  return (run_stop_time_ - run_start_time_).count();
}
void dimkashelk::Order::set_put_in()
{
  put_in_stack_time_ = std::chrono::system_clock::now();
}
void dimkashelk::Order::set_put_out()
{
  run_start_time_ = put_out_stack_time_ = std::chrono::system_clock::now();
}
void dimkashelk::Order::set_run_stop()
{
  run_stop_time_ = std::chrono::system_clock::now();
}
