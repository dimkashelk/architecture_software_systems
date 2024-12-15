#ifndef ROBOT_H
#define ROBOT_H
#include <atomic>
#include <condition_variable>
#include <optional>
#include <mutex>
#include <thread>
#include <Order/order.h>

namespace dimkashelk
{
  class Robot
  {
  public:
    explicit Robot(size_t id);
    void set_order(const std::shared_ptr < Order > &order);
    void start_order();
    bool available() const;
    std::string to_string() const;
    ~Robot();

  private:
    void finish_order();
    void run();
    size_t calculate_wait_time() const;
    size_t id_;
    std::optional < std::shared_ptr < Order > > current_order_{};
    bool work_now_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_{};
    std::condition_variable cv_{};
    std::thread worker_thread_{};
  };
}
#endif
