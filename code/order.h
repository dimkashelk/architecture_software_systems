#ifndef ORDER_H
#define ORDER_H
#include "execution_status.h"

namespace dimkashelk
{
  namespace details
  {
    class Counter
    {
    public:
      size_t get_id()
      {
        ++id;
        return id;
      }
      static Counter *get_obj()
      {
        if (_obj == nullptr)
        {
          _obj = new Counter();
        }
        return _obj;
      }

    private:
      Counter():
        id(0)
      {}
      size_t id;
      static Counter *_obj;
    };
  }

  class Order
  {
  public:
    Order() = delete;
    Order(const Order &other) = default;
    Order(Order &&other) = default;
    Order &operator=(Order other) = default;
    Order &operator=(Order &&other) = default;
    Order(size_t from, size_t to);
    void set_status(ExecutionStatus status) noexcept;
    ExecutionStatus get_status() const noexcept;
    size_t get_id() const noexcept;
    size_t get_from() const noexcept;
    size_t get_to() const noexcept;
    ~Order() = default;

  private:
    size_t _id;
    size_t _from;
    size_t _to;
    ExecutionStatus _status;
  };
}
#endif
