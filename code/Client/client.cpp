#include "client.h"
#include <cstdlib>
#include <ctime>
void dimkashelk::Client::generate_order()
{
  std::srand(static_cast < unsigned >(std::time(nullptr)));
  const size_t from = static_cast < size_t >(std::rand() % 100);
  size_t to = static_cast < size_t >(std::rand() % 100);;
  while (to == from)
  {
    to = static_cast < size_t >(std::rand() % 100);
  }
  Order new_order(from, to);
  orders_.emplace_back(new_order);
}
