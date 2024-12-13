#ifndef CLIENT_H
#define CLIENT_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Order/order.h>

namespace dimkashelk
{
  class Client
  {
  public:
    Client()
    {
      std::srand(static_cast < unsigned >(std::time(nullptr)));
    }
    void generate_order()
    {
      const size_t from = static_cast < size_t >(std::rand() % 100);
      size_t to = static_cast < size_t >(std::rand() % 100);;
      while (to == from)
      {
        to = static_cast < size_t >(std::rand() % 100);
      }
      Order new_order(from, to);
      orders_.emplace_back(new_order);
    }
    const std::vector < Order > &get_orders() const
    {
      return orders_;
    }

  private:
    std::vector < Order > orders_;
  };
}
#endif
