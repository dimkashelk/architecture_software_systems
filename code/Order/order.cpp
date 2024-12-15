#include "order.h"
#include <EventManager/eventmanager.h>
#include "counter.h"
dimkashelk::Order::Order(const size_t from, const size_t to):
  id_(details::Counter::get_obj()->get_id()),
  from_(from),
  to_(to),
  status_(EXECUTION_CREATE)
{}
std::string dimkashelk::Order::to_string() const
{
  return "Order{id=" + std::to_string(id_) + ", from=" + std::to_string(from_) + ", to=" + std::to_string(to_) +
         ", status=" + executionStatusToString(status_) + "}";
}
void dimkashelk::Order::set_status(const ExecutionStatus status) noexcept
{
  EventManager::getInstance().logEvent("(Order) Update status: " + to_string() + " to status: " + executionStatusToString(status_));
  status_ = status;
}
dimkashelk::ExecutionStatus dimkashelk::Order::get_status() const noexcept
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
