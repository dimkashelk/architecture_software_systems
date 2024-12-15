#ifndef CODER_H
#define CODER_H
#include <mutex>

namespace dimkashelk::details
{
  class Counter
  {
  public:
    size_t get_id();
    static Counter *get_obj()
    {
      std::lock_guard lock(static_mtx_);
      if (obj_ == nullptr)
      {
        obj_ = new Counter();
      }
      return obj_;
    }

  private:
    Counter() :
      id_(0)
    {
    }
    size_t id_;
    static Counter *obj_;
    static std::mutex static_mtx_;
    std::mutex mtx_;
  };
}
#endif
