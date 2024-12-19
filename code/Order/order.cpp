#include "order.h"
#include <eventmanager.h>
#include <counter.h>
dimkashelk::Order::Order(const size_t from, const size_t to):
  id_(details::Counter::get_obj()->get_id()),
  from_(from),
  to_(to),
  status_(EXECUTION_CREATE)
{
  EventManager::getInstance().logEvent(
    "(Order) create order with id=" + std::to_string(id_) + ", from=" + std::to_string(from_) + ", to=" +
    std::to_string(to_));
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
  if (status_ == EXECUTION_CREATE and status == EXECUTION_IN_STACK)
  {
    put_in_stack_time_ = std::chrono::system_clock::now();
  }
  else if (status_ == EXECUTION_IN_STACK and status == EXECUTION_RUN)
  {
    run_start_time_ = put_out_stack_time_ = std::chrono::system_clock::now();
  }
  else if (status_ == EXECUTION_RUN and
           (status == EXECUTION_FAILED or
            status == EXECUTION_DONE or
            status == EXECUTION_REJECTED))
  {
    run_stop_time_ = std::chrono::system_clock::now();
  }
  status_ = status;
}
dimkashelk::ExecutionStatus dimkashelk::Order::get_status() const
{
  return status_;
}
size_t dimkashelk::Order::get_id() const noexcept
{
  return id_;
}
size_t dimkashelk::Order::get_from() const noexcept
{
  return from_;
}
size_t dimkashelk::Order::get_to() const noexcept
{
  return to_;
}
void dimkashelk::Order::set_put_in()
{
  put_in_stack_time_ = std::chrono::system_clock::now();
}
void dimkashelk::Order::set_put_out()
{
  put_out_stack_time_ = std::chrono::system_clock::now();
}
void dimkashelk::Order::set_run_start()
{
  run_start_time_ = std::chrono::system_clock::now();
}
void dimkashelk::Order::set_run_stop()
{
  run_stop_time_ = std::chrono::system_clock::now();
}
