#include "orderallocator.h"
#include "order.h"
dimkashelk::Order *dimkashelk::OrderAllocator < dimkashelk::Order >::allocate(std::size_t n)
{
  if (n > std::size_t(-1) / sizeof(T))
  {
    throw std::bad_alloc();
  }
  T *ptr = static_cast < T * >(::operator new(n * sizeof(T)));
  return ptr;
}

