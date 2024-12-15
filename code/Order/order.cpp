#include "order.h"
#include "counter.h"
dimkashelk::Order::Order(const size_t from, const size_t to):
  _id(details::Counter::get_obj()->get_id()),
  _from(from),
  _to(to),
  _status(EXECUTION_CREATE)
{}
std::string dimkashelk::Order::to_string() const
{
  return "Order{id=" + std::to_string(_id) + ", from=" + std::to_string(_from) + ", to=" + std::to_string(_to) + ", status=" + std::to_string(_status) + "}";
}
void dimkashelk::Order::set_status(const ExecutionStatus status) noexcept
{
  _status = status;
}
dimkashelk::ExecutionStatus dimkashelk::Order::get_status() const noexcept
{
  return _status;
}
size_t dimkashelk::Order::get_id() const noexcept
{
  return _id;
}
size_t dimkashelk::Order::get_from() const noexcept
{
  return _from;
}
size_t dimkashelk::Order::get_to() const noexcept
{
  return _to;
}
