#ifndef ORDERALLOCATOR_H
#define ORDERALLOCATOR_H
#include <iostream>
#include <memory>
#include "order.h"

namespace dimkashelk
{
  class OrderAllocator
  {
  public:
    OrderAllocator() = default;
    Order *allocate(std::size_t n);
    void deallocate(Order *ptr, std::size_t n)
    {
      std::cout << "Deallocating " << n * sizeof(Order) << " bytes\n";
      ::operator delete(ptr);
    }
    template< typename U, typename... Args >
    void construct(U *ptr, Args &&... args)
    {
      std::cout << "Constructing object\n";
      new(ptr) U(std::forward < Args >(args)...);
    }
    template< typename U >
    void destroy(U *ptr)
    {
      std::cout << "Destroying object\n";
      ptr->~U();
    }
  };
  template< typename T, typename U >
  bool operator==(const OrderAllocator < T > &, const OrderAllocator < U > &)
  {
    return true;
  }
  template< typename T, typename U >
  bool operator!=(const OrderAllocator < T > &, const OrderAllocator < U > &)
  {
    return false;
  }
}
#endif
