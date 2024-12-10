#ifndef ORDERALLOCATOR_H
#define ORDERALLOCATOR_H
#include <memory>
#include "order.h"

namespace dimkashelk
{
  namespace details
  {
    class OrderAllocator
    {
    public:
      OrderAllocator() = default;
      Order *allocate(std::size_t n);
      void deallocate(Order *ptr, std::size_t n);
      template< typename U, typename... Args >
      void construct(U *ptr, Args &&... args);
      template< typename U >
      void destroy(U *ptr);
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
}
#endif
