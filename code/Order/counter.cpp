#include "counter.h"

namespace dimkashelk::details
{
  Counter *Counter::obj_ = nullptr;
  std::mutex Counter::static_mtx_;
  size_t Counter::get_id()
  {
    std::lock_guard lock(mtx_);
    return id_++;
  }
  Counter *Counter::get_obj()
  {
    std::lock_guard lock(static_mtx_);
    if (obj_ == nullptr)
    {
      obj_ = new Counter();
    }
    return obj_;
  }
}
