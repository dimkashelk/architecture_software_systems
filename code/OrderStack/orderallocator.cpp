#include "orderallocator.h"
#include "order.h"

namespace dimkashelk
{
  Order *OrderAllocator::allocate(const size_t n)
  {
    if (n > static_cast < size_t >(-1) / sizeof(Order))
    {
      throw std::bad_alloc();
    }
    auto *ptr = static_cast < Order * >(::operator new(n * sizeof(Order)));
    return ptr;
  }
  void OrderAllocator::deallocate(Order *ptr, const size_t n)
  {
    ::operator delete(ptr);
  }
  template< typename U, typename... Args >
  void OrderAllocator::construct(U *ptr, Args &&... args)
  {
    new(ptr) U(std::forward < Args >(args)...);
  }
}
