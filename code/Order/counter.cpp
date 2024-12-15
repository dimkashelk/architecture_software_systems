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
}
