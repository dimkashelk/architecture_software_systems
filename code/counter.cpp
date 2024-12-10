#include "counter.h"
namespace dimkashelk::details
{
  Counter *Counter::obj_ = nullptr;
  std::mutex Counter::static_mtx_;
}