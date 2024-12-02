#include "order.h"
dimkashelk::Order::Order(const size_t from, const size_t to):
  _id(details::Counter::get_obj()->get_id()),
  _from(from),
  _to(to),
  _status(ExecutionStatus::EXECUTION_CREATE)
{}
void dimkashelk::Order::set_status(const ExecutionStatus status)
{
  _status = status;
}
dimkashelk::ExecutionStatus dimkashelk::Order::get_status() const
{
  return _status;
}
