#ifndef CLIENT_H
#define CLIENT_H
#include <vector>
#include <Order/order.h>

namespace dimkashelk
{
  class Client
  {
  public:
    Client();
    void generate_order();
    const std::vector < Order > &get_orders() const
    {
      return orders_;
    }

  private:
    std::vector < Order > orders_;
  };
}
#endif
