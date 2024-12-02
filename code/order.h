#ifndef ORDER_H
#define ORDER_H
#include "execution_status.h"

namespace dimkashelk
{
  class Order
  {
  public:
    Order(size_t from, size_t to);
    void set_status(ExecutionStatus status);
    ExecutionStatus get_status() const;
    size_t get_id() const;
    size_t get_from() const;
    size_t get_to() const;

  private:
    size_t _id;
    size_t _from;
    size_t _to;
    ExecutionStatus _status;
  };
}
#endif
